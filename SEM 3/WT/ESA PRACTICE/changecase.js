// Write a JavaScript function to take a string as input parameter and reverse the
// case of every alphabet in the string. The function should return the modified
// string.
// Ex. changeCase( HeLlo") must return "hEILO".

function changeCase(inputString) {
    let result = '';
    for (let char of inputString) {
        if (char === char.toUpperCase()) {
            result += char.toLowerCase();
        } else {
            result += char.toUpperCase();
        }
    }
    return result;
}

// Example usage
console.log(changeCase("HeLlo")); // Output: "hElLO"
