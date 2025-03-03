//computron.cpp

#include "computron.h"

#include <fstream>
#include <iomanip>

void load_from_file(std::array<int, memorySize>& memory, const std::string& filename) {

    constexpr int sentinel{-99999};// terminates reading after -99999
    size_t i{0}; 
    std::string line;
    int instruction;


    std::ifstream inputFile(filename); 
        if (!inputFile) 
        {
            // throw runtime_error exception with string "invalid_input"
            throw std::runtime_error("invalid_input");
        }
            

        while (std::getline(inputFile, line)) {
            instruction = std::stoi(line); 
            if (instruction == sentinel)
            {
                break; 
            }
            // Check if the instruction is valid using the validWord function
            // If the instruction is valid, store it in memory at position 'i' and increment 'i'
            // If the instruction is invalid, throw a runtime error with the message "invalid_input"
            if (validWord(instruction))
            {
                //Valid instruction, stores in memory at position i
                memory[i] = instruction;
                i++;
            }
            else
            {
                //Invalid instruction, throw exception
                throw std::runtime_error("invalid_input");
            }
        }
    inputFile.close();
}


Command opCodeToCommand(size_t opCode){
    switch(opCode){
        case 10: return Command::read;
        // ToDo: Complete
        case 11: return Command::write;
        case 20: return Command::load;
        case 21: return Command::store;
        case 30: return Command::add;
        case 31: return Command::subtract;
        case 32: return Command::divide;
        case 33: return Command::multiply;
        case 40: return Command::branch;
        case 41: return Command::branchNeg;
        case 42: return Command::branchZero;
        case 43: return Command::halt;
        default: return Command::halt;
    };
}

void execute(std::array<int, memorySize>& memory, int* const acPtr, size_t* const icPtr, int* const irPtr, size_t* const opCodePtr, size_t* const opPtr, const std::vector<int>& inputs)
{

    size_t inputIndex{0}; // Tracks input

    //Initializes variables
    int accumulator{0};
    int instructionCounter{0};
    int instructionRegister{0};
    int operationCode{0};
    int operand{0};
    int word{0};

    do{
        //instruction counter to register
        instructionRegister = memory [instructionCounter];
        operationCode = instructionRegister / 100; // divide
        operand = instructionRegister % 100; // remainder
        

        switch(opCodeToCommand(operationCode)){

        case Command::read:
            word = inputs[inputIndex];
            // Assign the value of 'word' to the memory location pointed to by 'opPtr'

            //The location is the operand

            memory[operand] = word;

            //Increment for next input value
            inputIndex++;

            //Increment to the next memory value for next instruction
            instructionCounter++;
            

            break;
        
        case Command::write:
            //Dereference 'icPtr' to access the instruction counter and increment its value by 1
            
            //Gets the word to write at the specified location
            word = memory[operand];

            // use the below cout if needed but comment before submission
            std::cout << "Contents of " << std::setfill('0') << std::setw(2) << operand << " : " << memory[operand] << "\n";

            //Increments to the next memory value for the next instruction
            instructionCounter++;
            
            
            break;
        
        case Command::load:
            //Load the value from the memory location pointed to by 'opPtr' into the accumulator (acPtr)
            
            accumulator = memory[operand];
            

            //Increment the instruction counter (icPtr) to point to the next instruction
            instructionCounter++;
            

            break;

        case Command::store:
            // Store the value in the accumulator (acPtr) into the memory location pointed to by 'opPtr'
            
            memory[operand] = accumulator;

            // Increment the instruction counter (icPtr) to move to the next instruction
            instructionCounter++;
            

            break;

        case Command::add:
            // Add the value in the accumulator (acPtr) to the value in memory at the location pointed to by 'opPtr' and store the result in 'word'
            // If the result is valid, store it in the accumulator and increment the instruction counter
            // / If the result is invalid, throw a runtime error 

            word = accumulator + memory[operand];

            //Check if sum is valid to be stored
            if (word > maxWord || word < minWord)
            {
                //Throw exception
                throw std::runtime_error("Add result not valid");
            }

            else
            {
                //Stores word in accumulator
                accumulator = word;
                *acPtr = word;
            }

            //Increments to next instruction
            instructionCounter++;
            

            break;

        case Command::subtract:
            // Subtract the value in memory at the location pointed to by 'opPtr' from the value in the accumulator (acPtr) and store the result in 'word'
            // If the result is valid, store it in the accumulator and increment the instruction counter
            // / If the result is invalid, throw a runtime error 

            word = accumulator - memory[operand];

            //Check if result is valid to be stored
            if (word > maxWord || word < minWord)
            {
                //Throw exception
                throw std::runtime_error("Add result not valid");
            }

            else
            {
                //Stores word in accumulator
                accumulator = word;
                
            }

            //Increments to next instruction
            
            instructionCounter++;

            break;

        case Command::multiply:
            // as above do it for multiplication

            word = accumulator * memory[operand];

            //Check if result is valid to be stored
            if (word > maxWord || word < minWord)
            {
                //Throw exception
                throw std::runtime_error("Add result not valid");
            }

            else
            {
                //Stores word in accumulator
                accumulator = word;
                
            }

            //Increments to next instruction
            instructionCounter++;
            

            break;

        case Command::divide:
            // as above do it for division

            word = accumulator / memory[operand];

            //Check if result is valid to be stored
            if (word > maxWord || word < minWord)
            {
                //Throw exception
                throw std::runtime_error("Add result not valid");
            }

            else
            {
                //Stores word in accumulator
                accumulator = word;
                
            }

            //Increments to next instruction
            instructionCounter++;
            

            break;

        case Command::branch:

            //Moves instruction counter to operand location
            instructionCounter = operand;

            
            break;
            
        case Command::branchNeg:

            //Moves instruction counter to operand location if accumulator is negative
            if (accumulator < 0)
            {
                instructionCounter = operand;
                
            }
            else
            {
                //Just increment instruction counter
                instructionCounter++;
                
            }

            //acPtr < 0 ? *icPtr = *opPtr : ++(*icPtr);
            break;
            
        case Command::branchZero:

            //Moves instruction counter to operand location if accumulator is zero
            if (accumulator == 0)
            {
                instructionCounter = operand;
                
            }
            else
            {
                //Just increment instruction counter
                instructionCounter++;
                
            }

            //*acPtr == 0 ? *icPtr = *opPtr : ++(*icPtr);
            break;
            
        case Command::halt:
            break;
            
        default:
            // any instruction required
            //Invalid operation, throw exception
            throw std::runtime_error("Invalid Command");
            break;
        };
        // You may modify the below while condition if required
    }while(opCodeToCommand(operationCode) != Command::halt);

//Updates pointer values
*acPtr = accumulator;
*icPtr = instructionCounter;
*irPtr = instructionRegister;
*opCodePtr = operationCode;
*opPtr = operand;

};


bool validWord(int word){
    //Check if the word is outside the valid ranges
    if (word > maxWord || word < minWord)
    {
        return false;
    }

    //Check for empty memory space
    if (word == 0)
    {
        return true;
    }

    //Check if the operation code is valid
    int operationCode = word / 100;
    switch (operationCode)
    {
        case static_cast<int>(Command::read):
        case static_cast<int>(Command::write):
        case static_cast<int>(Command::load):
        case static_cast<int>(Command::store):
        case static_cast<int>(Command::add):
        case static_cast<int>(Command::subtract):
        case static_cast<int>(Command::divide):
        case static_cast<int>(Command::multiply):
        case static_cast<int>(Command::branch):
        case static_cast<int>(Command::branchNeg):
        case static_cast<int>(Command::branchZero):
        case static_cast<int>(Command::halt):
            return true;
        default:
            return false;

    }

};

void dump(std::array<int, memorySize>& memory, int accumulator, 
            size_t instructionCounter, size_t instructionRegister,
            size_t operationCode, size_t operand){
    //Todo
    
    //Prints the necessary values
    std::cout << "Registers" << std::endl;
    std::cout << "accumulator " << accumulator << std::endl;
    std::cout << "instructionCounter " << instructionCounter << std::endl;
    std::cout << "instructionRegister " << instructionRegister << std::endl;
    std::cout << "operationCode " << operationCode << std::endl;
    std::cout << "operand " << operand << std::endl;

    //Prints memory values
    
    //First headers
    std::cout << "   " << std::endl;
    std::cout << "Memory:" << std::endl;

    std::cout << "        ";
    for (int i = 0; i < 10; i++)
    {
        std::cout << i << "     ";
    }

    std::cout << std::endl;

    //Then each line of memory
    for (int i = 0; i < 10; i++)
    {

        std::cout << i << "0" << "    ";

        for (int j = 0; j < 10; j++)
        {
            int location = (10 * i) + j;
            //Do either + or - sign appropriately
            if (memory[location] < 0)
            {
                std::cout << "-" << std::setfill('0') << std::setw(4) << memory[location] << " ";
            }
            else
            {
                std::cout << "+" << std::setfill('0') << std::setw(4) << memory[location] << " ";
            }
            
        }

        std::cout << std::endl;

    }

};