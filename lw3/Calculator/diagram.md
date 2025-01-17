```mermaid
classDiagram
    class CCalculatorController {
        -CCalculator& m_calculator
        -istream& m_input
        -ostream& m_output
        -ActionMap m_actionMap
        +HandleCommand(): void
        -PrintAvailableVariables(): void const
        -PrintAvailableFunctions(): void const
        -DefineVariable(): void
        -UpdateVariable(): void
        -DefineFunction(): void
        -PrintIdentifier(): void const
    }

    class CCalculator {
        -VariablesMap m_variablesMap
        -FunctionsMap m_functionsMap
        +DefineVariable(identifier: string)
        +UpdateVariable(identifier: string, value: double): void
        +DefineFunction(identifier: string, operand: string): void
        +DefineFunction(identifier: string, leftOperand: string, Operation operation, rightOperand: string): void
    }

    class CVariable {
        -double m_value
        +GetValue(): double
        +HasValue(): void const
        +CalculateValue(): void
        +RegisterObserver(IObserver & observer): void
        +RemoveObserver(): void
        +NotifyObservers(): void
        +SetValue(): void
    }

    class CFunction {
        -double m_value
        -Operaion m_operation
        +GetVaue(): double
        +HasValue(): void const
        +CalculateValue(): void
        +Update(): void
        -ClearCache(): void
    }

    class IValueProvider {
        <<interface>>
        +GetValue(): double
        +HasValue(): void const
        +CalculateValue(): void
        -Calculate(): double
    }

    class IObservable {
        <<interface>>
        +RegisterObserver(IObserver & observer): void
        +RemoveObserver(): void
        +NotifyObservers(): void
    }

    class IObserver {
        <<interface>>
        +Update(): void
    }

    CCalculatorController o-- CCalculator
    CVariable ..|> IObservable
    CCalculator *-- CVariable
    CCalculator *-- CFunction
    CVariable ..|> IValueProvider
    CFunction ..|> IValueProvider
    CFunction ..|> IObserver
    IObservable ..> IObserver

```