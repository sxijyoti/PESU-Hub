import sys
import importlib
import argparse
import torch
import pandas as pd
import numpy as np
from sklearn.preprocessing import LabelEncoder
from sklearn.metrics import confusion_matrix, classification_report
import matplotlib.pyplot as plt
import seaborn as sns

parser = argparse.ArgumentParser()
parser.add_argument("--ID", required=True)
parser.add_argument("--data", default=None, required=True)
parser.add_argument("--framework", choices=['pytorch', 'sklearn'], default='pytorch')
parser.add_argument("--print-tree", action='store_true', help='Print the decision tree structure')
parser.add_argument("--print-construction", action='store_true', help='Print detailed tree construction process')

args = parser.parse_args()
subname = args.ID
data_path = args.data
framework = args.framework
print_tree_flag = args.print_tree
print_construction_flag = args.print_construction

try:
    mymodule = importlib.import_module(subname)
except Exception as e:
    print("Rename your written program as CAMPUS_SECTION_SRN_Lab3.py and run python test.py --ID CAMPUS_SECTION_SRN_Lab3 --data mushroom_data.csv --framework [pytorch|sklearn] [--print-tree] [--print-construction]")
    sys.exit()

get_selected_attribute = mymodule.get_selected_attribute
get_information_gain = mymodule.get_information_gain
get_avg_info_of_attribute = mymodule.get_avg_info_of_attribute
get_entropy_of_dataset = mymodule.get_entropy_of_dataset


def calculate_accuracy(y_true, y_pred):
    if len(y_true) != len(y_pred):
        raise ValueError("y_true and y_pred must have the same length")
    
    if isinstance(y_true, torch.Tensor):
        y_true = y_true.numpy()
    if isinstance(y_pred, torch.Tensor):
        y_pred = y_pred.numpy()
    
    valid_mask = np.array([pred is not None for pred in y_pred])
    if not np.any(valid_mask):
        return 0.0
    
    y_true_valid = y_true[valid_mask]
    y_pred_valid = np.array(y_pred)[valid_mask]
    
    correct = np.sum(y_true_valid == y_pred_valid)
    total = len(y_true_valid)
    
    return correct / total if total > 0 else 0.0

def calculate_precision_recall_f1(y_true, y_pred, average='weighted'):
    if len(y_true) != len(y_pred):
        raise ValueError("y_true and y_pred must have the same length")
    
    if isinstance(y_true, torch.Tensor):
        y_true = y_true.numpy()
    if isinstance(y_pred, torch.Tensor):
        y_pred = y_pred.numpy()
    
    valid_mask = np.array([pred is not None for pred in y_pred])
    if not np.any(valid_mask):
        return 0.0, 0.0, 0.0
    
    y_true_valid = y_true[valid_mask]
    y_pred_valid = np.array(y_pred)[valid_mask]
    
    classes = np.unique(np.concatenate([y_true_valid, y_pred_valid]))
    
    if average == 'weighted':
        precisions, recalls, f1s, supports = [], [], [], []
        
        for cls in classes:
            tp = np.sum((y_true_valid == cls) & (y_pred_valid == cls))
            fp = np.sum((y_true_valid != cls) & (y_pred_valid == cls))
            fn = np.sum((y_true_valid == cls) & (y_pred_valid != cls))
            
            precision = tp / (tp + fp) if (tp + fp) > 0 else 0.0
            recall = tp / (tp + fn) if (tp + fn) > 0 else 0.0
            f1 = 2 * precision * recall / (precision + recall) if (precision + recall) > 0 else 0.0
            support = np.sum(y_true_valid == cls)
            
            precisions.append(precision)
            recalls.append(recall)
            f1s.append(f1)
            supports.append(support)
        
        total_support = sum(supports)
        if total_support == 0:
            return 0.0, 0.0, 0.0
            
        weighted_precision = sum(p * s for p, s in zip(precisions, supports)) / total_support
        weighted_recall = sum(r * s for r, s in zip(recalls, supports)) / total_support
        weighted_f1 = sum(f * s for f, s in zip(f1s, supports)) / total_support
        
        return weighted_precision, weighted_recall, weighted_f1
    
    elif average == 'macro':
        precisions, recalls, f1s = [], [], []
        
        for cls in classes:
            tp = np.sum((y_true_valid == cls) & (y_pred_valid == cls))
            fp = np.sum((y_true_valid != cls) & (y_pred_valid == cls))
            fn = np.sum((y_true_valid == cls) & (y_pred_valid != cls))
            
            precision = tp / (tp + fp) if (tp + fp) > 0 else 0.0
            recall = tp / (tp + fn) if (tp + fn) > 0 else 0.0
            f1 = 2 * precision * recall / (precision + recall) if (precision + recall) > 0 else 0.0
            
            precisions.append(precision)
            recalls.append(recall)
            f1s.append(f1)
        
        return np.mean(precisions), np.mean(recalls), np.mean(f1s)

def calculate_per_class_metrics(y_true, y_pred):
    if len(y_true) != len(y_pred):
        raise ValueError("y_true and y_pred must have the same length")
    
    if isinstance(y_true, torch.Tensor):
        y_true = y_true.numpy()
    if isinstance(y_pred, torch.Tensor):
        y_pred = y_pred.numpy()
    
    valid_mask = np.array([pred is not None for pred in y_pred])
    if not np.any(valid_mask):
        return {}
    
    y_true_valid = y_true[valid_mask]
    y_pred_valid = np.array(y_pred)[valid_mask]
    
    classes = np.unique(np.concatenate([y_true_valid, y_pred_valid]))
    metrics = {}
    
    for cls in classes:
        tp = np.sum((y_true_valid == cls) & (y_pred_valid == cls))
        fp = np.sum((y_true_valid != cls) & (y_pred_valid == cls))
        fn = np.sum((y_true_valid == cls) & (y_pred_valid != cls))
        tn = np.sum((y_true_valid != cls) & (y_pred_valid != cls))
        
        precision = tp / (tp + fp) if (tp + fp) > 0 else 0.0
        recall = tp / (tp + fn) if (tp + fn) > 0 else 0.0
        f1 = 2 * precision * recall / (precision + recall) if (precision + recall) > 0 else 0.0
        specificity = tn / (tn + fp) if (tn + fp) > 0 else 0.0
        support = np.sum(y_true_valid == cls)
        
        metrics[cls] = {
            'precision': precision,
            'recall': recall,
            'f1_score': f1,
            'specificity': specificity,
            'support': support,
            'true_positives': tp,
            'false_positives': fp,
            'false_negatives': fn,
            'true_negatives': tn
        }
    
    return metrics

def calculate_tree_complexity_metrics(tree):
    if isinstance(tree, int) or tree is None:
        return {
            'max_depth': 0,
            'num_nodes': 1,
            'num_leaves': 1,
            'num_internal_nodes': 0
        }
    
    if not isinstance(tree, dict):
        return {
            'max_depth': 0,
            'num_nodes': 1,
            'num_leaves': 1,
            'num_internal_nodes': 0
        }
    
    def get_tree_stats(node, depth=0):
        if isinstance(node, int) or node is None:
            return {
                'max_depth': depth,
                'num_nodes': 1,
                'num_leaves': 1,
                'num_internal_nodes': 0
            }
        
        if not isinstance(node, dict) or 'branches' not in node:
            return {
                'max_depth': depth,
                'num_nodes': 1,
                'num_leaves': 1,
                'num_internal_nodes': 0
            }
        
        max_depth = depth
        total_nodes = 1
        total_leaves = 0
        total_internal = 1
        
        for branch_value, subtree in node['branches'].items():
            subtree_stats = get_tree_stats(subtree, depth + 1)
            max_depth = max(max_depth, subtree_stats['max_depth'])
            total_nodes += subtree_stats['num_nodes']
            total_leaves += subtree_stats['num_leaves']
            total_internal += subtree_stats['num_internal_nodes']
        
        return {
            'max_depth': max_depth,
            'num_nodes': total_nodes,
            'num_leaves': total_leaves,
            'num_internal_nodes': total_internal
        }
    
    return get_tree_stats(tree)

def evaluate_decision_tree(tree, X_test, y_test, cols, class_names=None):

    predictions = []
    
    for i, sample in enumerate(X_test):
        pred = predict_single_sample(tree, sample, cols)
        predictions.append(pred)
    
    accuracy = calculate_accuracy(y_test, predictions)
    precision, recall, f1 = calculate_precision_recall_f1(y_test, predictions, average='weighted')
    precision_macro, recall_macro, f1_macro = calculate_precision_recall_f1(y_test, predictions, average='macro')
    
    per_class_metrics = calculate_per_class_metrics(y_test, predictions)
    
    tree_stats = calculate_tree_complexity_metrics(tree)
    
    print(f"\n📊 OVERALL PERFORMANCE METRICS")
    print(f"{'='*40}")
    print(f"Accuracy:             {accuracy:.4f} ({accuracy*100:.2f}%)")
    print(f"Precision (weighted): {precision:.4f}")
    print(f"Recall (weighted):    {recall:.4f}")
    print(f"F1-Score (weighted):  {f1:.4f}")
    print(f"Precision (macro):    {precision_macro:.4f}")
    print(f"Recall (macro):       {recall_macro:.4f}")
    print(f"F1-Score (macro):     {f1_macro:.4f}")
    
    print(f"\n🌳 TREE COMPLEXITY METRICS")
    print(f"{'='*40}")
    print(f"Maximum Depth:        {tree_stats['max_depth']}")
    print(f"Total Nodes:          {tree_stats['num_nodes']}")
    print(f"Leaf Nodes:           {tree_stats['num_leaves']}")
    print(f"Internal Nodes:       {tree_stats['num_internal_nodes']}")
    

    
    total_predictions = len(predictions)
    valid_predictions = sum(1 for p in predictions if p is not None)
    prediction_rate = valid_predictions / total_predictions if total_predictions > 0 else 0
    
    
    return {
        'accuracy': accuracy,
        'precision_weighted': precision,
        'recall_weighted': recall,
        'f1_weighted': f1,
        'precision_macro': precision_macro,
        'recall_macro': recall_macro,
        'f1_macro': f1_macro,
        'per_class_metrics': per_class_metrics,
        'tree_complexity': tree_stats,
        'predictions': predictions,
        'prediction_rate': prediction_rate
    }


def convert_data_for_framework(data, target_framework):
    if target_framework == 'pytorch':
        if isinstance(data, np.ndarray):
            return torch.tensor(data, dtype=torch.float32)
        return data
    else:
        if isinstance(data, torch.Tensor):
            return data.numpy()
        return data

def get_unique_values(data, column_idx, target_framework):
    if target_framework == 'pytorch':
        if isinstance(data, torch.Tensor):
            return torch.unique(data[:, column_idx])
        else:
            tensor_data = torch.tensor(data, dtype=torch.float32)
            return torch.unique(tensor_data[:, column_idx])
    else:
        if isinstance(data, np.ndarray):
            return np.unique(data[:, column_idx])
        else:
            return np.unique(data.numpy()[:, column_idx])

def get_unique_with_counts(data, column_idx, target_framework):
    """Get unique values and counts in a framework-agnostic way"""
    if target_framework == 'pytorch':
        if isinstance(data, torch.Tensor):
            return torch.unique(data[:, column_idx], return_counts=True)
        else:
            tensor_data = torch.tensor(data, dtype=torch.float32)
            return torch.unique(tensor_data[:, column_idx], return_counts=True)
    else:  # sklearn/numpy
        if isinstance(data, np.ndarray):
            return np.unique(data[:, column_idx], return_counts=True)
        else:
            return np.unique(data.numpy()[:, column_idx], return_counts=True)

def create_mask(data, column_idx, value, target_framework):
    """Create boolean mask in a framework-agnostic way"""
    if target_framework == 'pytorch':
        if isinstance(data, torch.Tensor):
            return data[:, column_idx] == value
        else:
            tensor_data = torch.tensor(data, dtype=torch.float32)
            return tensor_data[:, column_idx] == value
    else:  # sklearn/numpy
        if isinstance(data, np.ndarray):
            return data[:, column_idx] == value
        else:
            return data.numpy()[:, column_idx] == value

def get_item_value(value, target_framework):
    """Extract scalar value in a framework-agnostic way"""
    if target_framework == 'pytorch':
        if hasattr(value, 'item'):
            return value.item()
        return float(value)
    else:  # sklearn/numpy
        if isinstance(value, np.ndarray):
            return value.item() if value.size == 1 else value
        return float(value)

def preprocess_data(df):
    """
    Preprocess the dataset by encoding categorical variables
    The last column is automatically treated as the target variable
    """

    df_processed = df.copy()
    

    print("Original dataset info:")
    print(f"Shape: {df.shape}")
    print(f"Columns: {list(df.columns)}")
    print("\nFirst few rows:")

    
    label_encoders = {}
    for column in df_processed.columns:
        le = LabelEncoder()
        df_processed[column] = le.fit_transform(df_processed[column])
        label_encoders[column] = le
        

        if column in list(df.columns)[:3] or column == df.columns[-1]:  
            unique_orig = df[column].unique()[:5]  
            unique_encoded = df_processed[column].unique()[:5]
            print(f"\n{column}: {unique_orig} -> {unique_encoded}")
    
    return df_processed, label_encoders

def construct_tree(data, cols, used_attributes=None, level=0, max_depth=5, target_framework='pytorch', print_construction=False):
    """
    Recursively construct decision tree using ID3 algorithm
    Assumes last column is the target variable
    Returns: Tree structure (dict for internal nodes, int for leaf nodes)
    """
    if used_attributes is None:
        used_attributes = set()
    
    # Base case: empty data
    if len(data) == 0:
        return None
    
    # Convert data to appropriate framework format
    framework_data = convert_data_for_framework(data, target_framework)
    
    # Print the entropy of the current dataset
    entropy = get_entropy_of_dataset(framework_data)
    if print_construction:
        print_node_info(f"Entropy = {entropy:.4f}", level)
    
    # Base case: pure node (entropy = 0)
    if entropy == 0:
        # Get the class (all samples have same class)
        if target_framework == 'pytorch':
            if isinstance(data, torch.Tensor):
                target_values = data[:, -1]
            else:
                target_values = torch.tensor(data)[:, -1]
            majority_class = int(target_values[0].item())  # All same, so take first
        else:
            if isinstance(data, np.ndarray):
                target_values = data[:, -1]
            else:
                target_values = np.array(data)[:, -1]
            majority_class = int(target_values[0])  # All same, so take first
        
        if print_construction:
            print_node_info(f"Hypothesis: Class {majority_class}", level)
        return majority_class
    
    # Base case: max depth reached
    if level >= max_depth:
        # Get majority class
        unique_vals, counts = get_unique_with_counts(data, -1, target_framework)
        if target_framework == 'pytorch':
            majority_idx = torch.argmax(counts)
            majority_class = int(get_item_value(unique_vals[majority_idx], target_framework))
        else:
            majority_idx = np.argmax(counts)
            majority_class = int(get_item_value(unique_vals[majority_idx], target_framework))
        
        if print_construction:
            print_node_info(f"Hypothesis: Class {majority_class} (max depth reached)", level)
        return majority_class
    
    # Base case: no more attributes available
    num_features = len(cols) - 1  
    if len(used_attributes) >= num_features:
        # Get majority class
        unique_vals, counts = get_unique_with_counts(data, -1, target_framework)
        if target_framework == 'pytorch':
            majority_idx = torch.argmax(counts)
            majority_class = int(get_item_value(unique_vals[majority_idx], target_framework))
        else:
            majority_idx = np.argmax(counts)
            majority_class = int(get_item_value(unique_vals[majority_idx], target_framework))
        
        if print_construction:
            print_node_info(f"Hypothesis: Class {majority_class} (no more attributes)", level)
        return majority_class
    
    # Get the selected attribute and information gains
    try:
        gain_dict, selected_attribute = get_selected_attribute(framework_data)
        
        # Filter out already used attributes
        available_gains = {attr: gain for attr, gain in gain_dict.items() 
                          if attr not in used_attributes}
        
        # Base case: no available attributes or no information gain
        if not available_gains or max(available_gains.values()) <= 0:
            unique_vals, counts = get_unique_with_counts(data, -1, target_framework)
            if target_framework == 'pytorch':
                majority_idx = torch.argmax(counts)
                majority_class = int(get_item_value(unique_vals[majority_idx], target_framework))
            else:
                majority_idx = np.argmax(counts)
                majority_class = int(get_item_value(unique_vals[majority_idx], target_framework))
            
            if print_construction:
                print_node_info(f"Hypothesis: Class {majority_class} (no gain)", level)
            return majority_class
        

        selected_attribute = max(available_gains, key=available_gains.get)
        
        if print_construction:
            print_node_info(f"Selected Attribute: {cols[selected_attribute]} (gain: {available_gains[selected_attribute]:.4f})", level)
        

        tree_node = {
            'attribute': selected_attribute,
            'attribute_name': cols[selected_attribute],
            'gain': available_gains[selected_attribute],
            'level': level,
            'branches': {}
        }

        unique_values = get_unique_values(data, selected_attribute, target_framework)
        new_used_attributes = used_attributes.copy()
        new_used_attributes.add(selected_attribute)
        

        for value in unique_values:
            mask = create_mask(data, selected_attribute, value, target_framework)
            
            if target_framework == 'pytorch':
                if isinstance(data, torch.Tensor):
                    subset_data = data[mask]
                else:
                    tensor_data = torch.tensor(data, dtype=torch.float32)
                    subset_data = tensor_data[mask]
            else:  # sklearn/numpy
                if isinstance(data, np.ndarray):
                    subset_data = data[mask]
                else:
                    subset_data = data.numpy()[mask]
            
            value_int = int(get_item_value(value, target_framework))
            
            # Handle empty subset - assign majority class from current node
            if len(subset_data) == 0:
                unique_vals, counts = get_unique_with_counts(data, -1, target_framework)
                if target_framework == 'pytorch':
                    majority_idx = torch.argmax(counts)
                    majority_class = int(get_item_value(unique_vals[majority_idx], target_framework))
                else:
                    majority_idx = np.argmax(counts)
                    majority_class = int(get_item_value(unique_vals[majority_idx], target_framework))
                
                if print_construction:
                    print_node_info(f"Branch {cols[selected_attribute]} = {value_int} (empty subset)", level)
                tree_node['branches'][value_int] = majority_class
                continue
            
            if print_construction:
                print_node_info(f"Branch {cols[selected_attribute]} = {value_int}", level)
            
            # RECURSIVE CALL - STORE THE RESULT!
            subtree = construct_tree(
                subset_data, 
                cols, 
                new_used_attributes, 
                level + 1, 
                max_depth, 
                target_framework,
                print_construction
            )
            

            tree_node['branches'][value_int] = subtree
        
        return tree_node
        
    except Exception as e:
        if print_construction:
            print_node_info(f"Error in tree construction: {e}", level)
        # Return majority class as fallback
        try:
            unique_vals, counts = get_unique_with_counts(data, -1, target_framework)
            if target_framework == 'pytorch':
                majority_idx = torch.argmax(counts)
                majority_class = int(get_item_value(unique_vals[majority_idx], target_framework))
            else:
                majority_idx = np.argmax(counts)
                majority_class = int(get_item_value(unique_vals[majority_idx], target_framework))
            return majority_class
        except:
            return None


def predict_single_sample(tree, sample, cols):
    """
    Predict class for a single sample using the constructed tree
    
    Args:
        tree: The constructed decision tree (dict or int)
        sample: Single data sample (list or array)
        cols: Column names
    
    Returns:
        Predicted class (int) or None if prediction fails
    """

    if isinstance(tree, int):
        return tree
    

    if not isinstance(tree, dict) or 'attribute' not in tree:
        return None
    

    attribute_idx = tree['attribute']

    if attribute_idx >= len(sample):
        return None
    
    attribute_value = int(sample[attribute_idx])
    

    if attribute_value not in tree['branches']:
        return None
    

    subtree = tree['branches'][attribute_value]

    return predict_single_sample(subtree, sample, cols)


def predict_batch(tree, data, cols):
    """
    Predict classes for multiple samples
    
    Args:
        tree: The constructed decision tree
        data: Array of samples (each row is a sample)
        cols: Column names
    
    Returns:
        List of predicted classes
    """
    predictions = []
    
    for sample in data:
        pred = predict_single_sample(tree, sample, cols)
        predictions.append(pred)
    
    return predictions


def print_tree_structure(tree, cols, level=0, prefix=""):
    """
    Pretty print the tree structure
    
    Args:
        tree: The constructed decision tree
        cols: Column names  
        level: Current depth level
        prefix: String prefix for indentation
    """
    if isinstance(tree, int):
        print(f"{prefix}├── Class {tree}")
        return
    
    if not isinstance(tree, dict) or 'attribute' not in tree:
        print(f"{prefix}├── None")
        return
    
    attr_name = tree['attribute_name']
    gain = tree.get('gain', 0)
    
    if level == 0:
        print(f"Root [{attr_name}] (gain: {gain:.4f})")
    
    branches = tree['branches']
    branch_items = list(branches.items())
    
    for i, (value, subtree) in enumerate(branch_items):
        is_last = (i == len(branch_items) - 1)
        
        if level == 0:
            print(f"├── = {value}:")
            new_prefix = "│   "
        else:
            branch_symbol = "└──" if is_last else "├──"
            print(f"{prefix}{branch_symbol} = {value}:")
            new_prefix = prefix + ("    " if is_last else "│   ")
        
        if isinstance(subtree, int):
            print(f"{new_prefix}├── Class {subtree}")
        elif isinstance(subtree, dict):
            attr_name = subtree['attribute_name']
            gain = subtree.get('gain', 0)
            print(f"{new_prefix}├── [{attr_name}] (gain: {gain:.4f})")
            print_tree_structure(subtree, cols, level + 1, new_prefix)
        else:
            print(f"{new_prefix}├── None")



def print_node_info(message, level):
    """Print formatted node information with proper indentation"""
    indent = "|  " * level
    print(f"Level {level}: Node Info - {indent}{message}")

def test_case():
    """Run test cases for the classification decision tree"""
    print(f"Running tests with {framework.upper()} framework")
    print("="*60)

    try:
        df = pd.read_csv(data_path)
        
        
    except Exception as e:
        print(f"Error loading dataset: {e}")
        return
    print(f" target column: '{df.columns[-1]}' (last column)")

    df_processed, label_encoders = preprocess_data(df)
    

    if framework == 'pytorch':
        dataset = torch.tensor(df_processed.values, dtype=torch.float32)
    else:  # sklearn
        dataset = df_processed.values.astype(np.float32)
    
    cols = list(df_processed.columns)
    
    print(f"\nProcessed dataset shape: {dataset.shape}")
    print(f"Number of features: {len(cols) - 1}")
    print(f"Features: {cols[:-1]}")  # All columns except last
    print(f"Target: {cols[-1]}")     # Last column
    print(f"Framework: {framework.upper()}")
    print(f"Data type: {type(dataset)}")
    
    
    

    try:
        print("\n" + "="*60)
        print("DECISION TREE CONSTRUCTION DEMO")
        print("="*60)

        total_samples = len(dataset)
        train_split = 0.8  
        train_size = int(total_samples * train_split)
        
        print(f"Total samples: {total_samples}")
        print(f"Training samples: {train_size}")
        print(f"Testing samples: {total_samples - train_size}")
        

        if framework == 'pytorch':
            torch.manual_seed(42)  
            indices = torch.randperm(total_samples)
            dataset_shuffled = dataset[indices]
            
            train_data = dataset_shuffled[:train_size]
            test_data = dataset_shuffled[train_size:]
        else:
            np.random.seed(42)  
            indices = np.random.permutation(total_samples)
            dataset_shuffled = dataset[indices]
            
            train_data = dataset_shuffled[:train_size]
            test_data = dataset_shuffled[train_size:]
        
        print(f"\nConstructing decision tree using training data...")
        tree = construct_tree(train_data, cols=cols, target_framework=framework, max_depth=7, print_construction=print_construction_flag)
        
        if tree is not None:
            print(f"\n🌳 Decision tree construction completed using {framework.upper()}!")
            
            if print_tree_flag:
                print(f"\n🌲 DECISION TREE STRUCTURE")
                print("="*60)
                print_tree_structure(tree, cols)
                print()

            if framework == 'pytorch':
                X_test = test_data[:, :-1] 
                y_test = test_data[:, -1]   
            else:
                X_test = test_data[:, :-1] 
                y_test = test_data[:, -1]   
       
            target_col = cols[-1] 
            if target_col in label_encoders:
        
                le = label_encoders[target_col]
                class_names = {i: le.inverse_transform([i])[0] for i in range(len(le.classes_))}
            else:
                class_names = None

            evaluation_results = evaluate_decision_tree(tree, X_test, y_test, cols, class_names)
            

          
             
        else:
            print("❌ Failed to construct decision tree!")
            
    except Exception as e:
        print(f"❌ Error in decision tree construction and evaluation: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    test_case()