/*
Author:         Frank Roscoe
Origin:         Object-Oriented Analysis course assignment
Refactored:     Extended and polished for Design Pattern Series portfolio
Date:           10/26/2025
Description:    Proof-of-concept demo illustrating the Strategy Design Pattern in C++.
                Demonstrates runtime selection of text formatting algorithms (uppercase, lowercase, title case)
                via interchangeable strategies, without modifying the context class.

Educational Walkthrough Notes:
                This project contains extensive inline comments. They are intentional:
                - To support my own learning process as a student.
                - To serve as a teaching aid for future students.
                - To demonstrate not just the code, but the reasoning behind design decisions.
                Note: This demo is intentionally comment-heavy for teaching clarity.
                In production or recruiter-facing projects, I write leaner, concise code.
                This version is part of my Design Pattern Series portfolio, blending education and professional practice.
*/

#include <iostream>
#include <string>
#include <cctype>
#include <memory>
using namespace std;

// Strategy Interface
// Instructional notes:
// - This is an abstract class defining the interface for text formatting strategies
// - It contains a pure virtual function and cannot be instantiated directly
// - It is used to define a common interface for different text formatting algorithms (derived classes)
// - The destructor is virtual to ensure proper cleanup of derived classes
// - Since C++ does not have built-in interface support, this sample app uses an abstract class
//   with pure virtual functions to achieve similar functionality
// - The superclass starts with 'I' to indicate it's an interface, following common conventions in C# and .NET.
//   This naming convention is not standard in C++, but is used here for clarity and cross-language teaching consistency
// - This allows for polymorphism, enabling the context class to use different formatting strategies interchangeably

class ITextFormatter {
public:
    // Pure virtual method that defines the formatting strategy
    // Accepts a constant reference to a string (to avoid copying) and returns a formatted string
    // Must be overridden by all concrete formatter classes
    virtual string format(const string& text) = 0;

    // Virtual destructor ensures proper cleanup of derived objects
    // when deleted through a base class pointer
    virtual ~ITextFormatter() {}
};

// Concrete Strategies: derived from the Strategy Interface
// Instructional notes:
// - These are concrete strategy classes that implement the ITextFormatter interface
// - Each class provides a specific text formatting algorithm
// - They override the format method to provide their unique behavior
// - These classes can be instantiated and used by the context class to format text in different ways
// - This demonstrates the Strategy Design Pattern, allowing the behavior of text formatting to be selected at runtime
// - Each concrete strategy class focuses on a single responsibility, adhering to the Single Responsibility Principle
// - New formatting strategies can be added easily without modifying existing code, following the Open/Closed Principle

// Concrete Strategy: Uppercase
// UpperCaseFormatter is a concrete strategy that implements the ITextFormatter interface
// It transforms the input string by converting all characters to uppercase
class UpperCaseFormatter : public ITextFormatter {
public:
    // Overrides the format method from the Interface superclass to apply uppercase transformation
    // Iterates through each character in the input string and converts it to uppercase
    string format(const string& text) override {
        string result = text;
        // Using range-based for loop to iterate through each character of the 'result' string
        // Chars are accessed by reference to modify them directly in-place to uppercase
        for (char& c : result) c = toupper(c);
        return result;
    }
};

// Concrete Strategy: Lowercase
// LowerCaseFormatter is a concrete strategy that implements the ITextFormatter interface
// It transforms the input string by converting all characters to lowercase
class LowerCaseFormatter : public ITextFormatter {
public:
    // Overrides the format method from the Interface superclass to apply lowercase transformation
    // Iterates through each character in the input string and converts it to lowercase
    string format(const string& text) override {
        string result = text;
        // Using range-based for loop to iterate through each character of the 'result' string
        // Chars are accessed by reference to modify them directly in-place to lowercase
        for (char& c : result) c = tolower(c);
        return result;
    }
};

// Concrete Strategy: Title Case
// TitleCaseFormatter is a concrete strategy that implements the ITextFormatter interface
// It transforms the input string by capitalizing the first letter of each word
class TitleCaseFormatter : public ITextFormatter {
public:
    string format(const string& text) override {
        string result = text;
        bool capitalize = true;

        // Using range-based for loop to iterate through each character of the 'result' string
        // The 'capitalize' flag tracks whether the current character is the start of a word
        for (char& c : result) {
            if (isspace(c)) {
                capitalize = true; // Next non-space character starts a new word
            }
            else if (capitalize) {
                c = toupper(c);    // Capitalize first letter of the word
                capitalize = false;
            }
            else {
                c = tolower(c);    // Lowercase the rest of the word
            }
        }
        return result;
    }
};

// Context Class: manages and applies a selected formatting strategy
// Educational Walkthrough Notes:
// - This class holds a smart pointer (unique_ptr) to the ITextFormatter interface
// - Using unique_ptr expresses exclusive ownership: TextProcessor owns the strategy object
// - Delegates formatting behavior to the currently assigned strategy object
// - The strategy can be changed dynamically at runtime using setFormatter()
// - Demonstrates the Strategy Design Pattern by decoupling formatting logic from the context
// - The context class does not implement formatting itself; it provides the environment in which a strategy operates
// - Supports scalability and flexibility: new strategies can be added without modifying the context
// - Adheres to the Open/Closed Principle (open to extension, closed to modification)
// - Uses composition (holding a strategy object) rather than inheritance, which increases flexibility
// - Modern C++ note: smart pointers eliminate the need for manual memory management and prevent leaks

class TextProcessor {
private:
    // Smart pointer to the current formatting strategy (implements ITextFormatter interface)
    // unique_ptr ensures exclusive ownership: only one TextProcessor can own a given strategy
    // When the TextProcessor object is destroyed or a new strategy is assigned, the old strategy
    // is automatically cleaned up
    unique_ptr<ITextFormatter> formatter;

public:
    // Constructor initializes the formatter smart pointer to nullptr (no strategy assigned by default)
    // unique_ptr can safely hold nullptr, representing 'no current strategy'
    TextProcessor() : formatter(nullptr) {}

    // Assigns a new formatting strategy at runtime
    // Ownership of the strategy object is transferred into the context using std::move
    // This enables dynamic selection of behavior without modifying the context class
    void setFormatter(unique_ptr<ITextFormatter> f) {
        formatter = move(f);
    }

    // Applies the currently assigned formatting strategy to the input text
    // If no strategy is set (formatter == nullptr), returns the original input unchanged
    // Educational note:
    // - 'formatter' is a unique_ptr<ITextFormatter> initialized to nullptr in the constructor
    // - It is set explicitly via the public setFormatter() method, so assignment happens outside the class (in main())
    // - Smart pointer semantics ensure safe cleanup when strategies are replaced or when TextProcessor goes out of scope
    string format(const string& text) {
        if (formatter)
            return formatter->format(text);
        else
            return text;
    }
};

// Main Function
int main() {
    // Create a TextProcessor object (context class)
    // This will be used to apply a selected text formatting strategy
    TextProcessor processor;
    string input;

    // Prompt the user to enter a sentence to be formatted
    cout << "Enter a sentence: ";
    // Read full line including spaces
    getline(cin, input);

    // Present formatting options to the user
    cout << "\nChoose a format:\n";
    cout << "1) Uppercase\n";
    cout << "2) Lowercase\n";
    cout << "3) Title Case\n";
    cout << "Enter choice (1-3): ";

    int choice;
    // Read user's formatting choice
    cin >> choice;

    // Based on user's choice, assign the appropriate concrete strategy to the context
    // Educational Walkthrough Notes:
    // - Each branch creates a new concrete strategy object using std::make_unique
    // - std::make_unique constructs the object and wraps it in a unique_ptr, ensuring safe ownership
    // - Ownership of the strategy is transferred into the TextProcessor via setFormatter()
    // - This demonstrates runtime flexibility: the context can switch strategies without modification
    // - Smart pointer semantics guarantee automatic cleanup when the strategy is replaced or goes out of scope
    switch (choice) {
    case 1:
        // Assign UpperCaseFormatter strategy
        // make_unique<UpperCaseFormatter>() creates a new UpperCaseFormatter and transfers ownership
        processor.setFormatter(make_unique<UpperCaseFormatter>());
        break;
    case 2:
        // Assign LowerCaseFormatter strategy
        // Ownership of the LowerCaseFormatter is safely moved into the context
        processor.setFormatter(make_unique<LowerCaseFormatter>());
        break;
    case 3:
        // Assign TitleCaseFormatter strategy
        // Demonstrates polymorphism: the context interacts with ITextFormatter, not the concrete class
        processor.setFormatter(make_unique<TitleCaseFormatter>());
        break;
    default:
        // If input is invalid, no strategy is assigned
        // The context remains with a nullptr strategy, so the original input is returned unchanged
        cout << "Invalid choice. Using default (no formatting).\n";
        break;
    }

    // Apply the selected formatting strategy to the input text
    // If no strategy was set, the original input is returned unchanged
    cout << "\nFormatted output:\n";
    cout << processor.format(input) << "\n";

    // Exit program
    return 0;
}
