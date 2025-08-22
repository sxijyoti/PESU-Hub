
import numpy as np
from collections import Counter

def get_entropy_of_dataset(data: np.ndarray) -> float:
    """
    Calculate the entropy of the entire dataset using the target variable (last column).
    
    Args:
        data (np.ndarray): Dataset where the last column is the target variable
    
    Returns:
        float: Entropy value calculated using the formula: 
               Entropy = -Σ(p_i * log2(p_i)) where p_i is the probability of class i
    
    Example:
        data = np.array([[1, 0, 'yes'],
                        [1, 1, 'no'],
                        [0, 0, 'yes']])
        entropy = get_entropy_of_dataset(data)
        # Should return entropy based on target column ['yes', 'no', 'yes']
    """
    # TODO: Implement entropy calculation
    # Hint: Use np.unique() to get unique classes and their counts
    # Hint: Handle the case when probability is 0 to avoid log2(0)
    lb = data[:, -1]   # last column = target
    _, counts = np.unique(lb, return_counts=True)
    prob = counts / counts.sum()
    prob = prob[prob > 0]  
    entropy = -np.sum(prob * np.log2(prob))
    return float(entropy)


def get_avg_info_of_attribute(data: np.ndarray, attribute: int) -> float:
    """
    Calculate the average information (weighted entropy) of a specific attribute.
    
    Args:
        data (np.ndarray): Dataset where the last column is the target variable
        attribute (int): Index of the attribute column to calculate average information for
    
    Returns:
        float: Average information calculated using the formula:
               Avg_Info = Σ((|S_v|/|S|) * Entropy(S_v)) 
               where S_v is subset of data with attribute value v
    
    Example:
        data = np.array([[1, 0, 'yes'],
                        [1, 1, 'no'],
                        [0, 0, 'yes']])
        avg_info = get_avg_info_of_attribute(data, 0)  # For attribute at index 0
        # Should return weighted average entropy for attribute splits
    """
    # TODO: Implement average information calculation
    # Hint: For each unique value in the attribute column:
    #   1. Create a subset of data with that value
    #   2. Calculate the entropy of that subset
    #   3. Weight it by the proportion of samples with that value
    #   4. Sum all weighted entropies
    values, counts = np.unique(data[:, attribute], return_counts=True)
    total = len(data)
    avg = 0.0

    for v, count in zip(values, counts):
        subset = data[data[:, attribute] == v]
        subset_labels = subset[:, -1]
        _, sub_counts = np.unique(subset_labels, return_counts=True)
        probs = sub_counts / sub_counts.sum()
        probs = probs[probs > 0]
        entropy_subset = -np.sum(probs * np.log2(probs))
        avg += (count / total) * entropy_subset

    return float(avg)


def get_information_gain(data: np.ndarray, attribute: int) -> float:
    """
    Calculate the Information Gain for a specific attribute.
    
    Args:
        data (np.ndarray): Dataset where the last column is the target variable
        attribute (int): Index of the attribute column to calculate information gain for
    
    Returns:
        float: Information gain calculated using the formula:
               Information_Gain = Entropy(S) - Avg_Info(attribute)
               Rounded to 4 decimal places
    
    Example:
        data = np.array([[1, 0, 'yes'],
                        [1, 1, 'no'],
                        [0, 0, 'yes']])
        gain = get_information_gain(data, 0)  # For attribute at index 0
        # Should return the information gain for splitting on attribute 0
    """
    # TODO: Implement information gain calculation
    # Hint: Information Gain = Dataset Entropy - Average Information of Attribute
    # Hint: Use the functions you implemented above
    # Hint: Round the result to 4 decimal places
    dataset_E = get_entropy_of_dataset(data)
    avg = get_avg_info_of_attribute(data, attribute)
    return round(dataset_E - avg, 4)

def get_selected_attribute(data: np.ndarray) -> tuple:
    """
    Select the best attribute based on highest information gain.
    
    Args:
        data (np.ndarray): Dataset where the last column is the target variable
    
    Returns:
        tuple: A tuple containing:
            - dict: Dictionary mapping attribute indices to their information gains
            - int: Index of the attribute with the highest information gain
    
    Example:
        data = np.array([[1, 0, 2, 'yes'],
                        [1, 1, 1, 'no'],
                        [0, 0, 2, 'yes']])
        result = get_selected_attribute(data)
        # Should return something like: ({0: 0.123, 1: 0.456, 2: 0.789}, 2)
        # where 2 is the index of the attribute with highest gain
    """
    # TODO: Implement attribute selection
    # Hint: Calculate information gain for all attributes (except target variable)
    # Hint: Store gains in a dictionary with attribute index as key
    # Hint: Find the attribute with maximum gain using max() with key parameter
    # Hint: Return tuple (gain_dictionary, selected_attribute_index)
    n_attr = data.shape[1] - 1
    info_gain = {}

    for attr in range(n_attr):
        ig = get_information_gain(data, attr)
        info_gain[attr] = ig

    selected_attr = max(info_gain, key=info_gain.get)
    return info_gain, selected_attr
