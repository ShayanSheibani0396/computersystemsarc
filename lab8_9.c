/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
// Please finish the following functions for lab 8.
// Lab 8 will perform the following functions:
//   1. Fetch the code stored in memory
//   2. Decode the code and prepare for the execution of the code.
//   3. Setup the execution function for CPU.

// Lab 9 will perform the following functions:
//   4. Execute the code stored in the memory and print the results.
#include "header.h"
#include "lab8header.h"
extern char *regNameTab[N_REG];
extern unsigned int PCRegister; // PC register, always pointing to the next instruction.

void CPU(char *mem){
    unsigned int machineCode = 0;
    unsigned char opcode = 0;
    PCRegister = CODESECTION;  // at the beginning, PCRegister is the starting point,
                       // it should be a global integer defined in header.h
    do{
        printf("\nPC:%x\n", PCRegister);
        machineCode = CPU_fetchCode(mem, PCRegister);
      if (machineCode == 0x00000000)  // quit the program when machineCode is 0, that is the end of the code.
          break;  // break the infinite loop.
        opcode = CPU_Decode(machineCode);
        printf("Decoded Opcode is: %02X. \n", opcode);
        CPU_Execution(opcode, machineCode, mem);

      // Lab 9: Finish the execution of the code.
      // Only finish this part when the CPU_Decode is done.

    }while (1);  // This is an infinite while loop
                 // When you fetch a machineCode of 00000000, the loop breaks.
    printRegisterFiles();     // After the code execution, print all the register contents on screen.
    printDataMemoryDump(mem); // After the code execution, print the memory dump of the data section.
}

// Lab 8 - Step 1. Finish the CPU_fectchCode function to
//         read the code section from memory and
//         get the 32-bit machine code from the memory.
unsigned int CPU_fetchCode(char *mem, int codeOffset){
    return read_dword(mem, codeOffset);

}

// Lab 8 - Step 2. Finish the CPU_Decode function to
//         decode the instruction and return the
//         opcode/function of the instruction.
//         Hints: Need to consider how to find the opcode/function from different types of instructions:
//                i.e., I-, J- and R-type instructions.
//                The return value should be a 6-bit bianry code.
unsigned char CPU_Decode(unsigned int machineCode)
{
    unsigned char opcode = (machineCode >> 26) & 0x3F;

    if (opcode == 0)
        return (machineCode & 0x3F); // R-type funct

    return opcode;
}
// R-type: opcode = 0
// I-type: normal opcode values
// J-type: opcode 2 or 3



// Lab 9: Finish the function CPU_Execution to run all the instructions.
void CPU_Execution(unsigned char opcode, unsigned int machineCode, char *mem)
{
    unsigned char rs, rt, rd;
    unsigned char realOpcode = (machineCode >> 26) & 0x3F;
    short immediate = 0;
    unsigned char funct;
    unsigned int address;

    switch (realOpcode)  // execute different functions when opcode is set differently.
    {
		// This is an example how lab will be executed. Please follow this example and finish exections of the code.
		// Hint: you need to implement the following instructions here:
		//       la, add, lb, bge, lw, sw, addi, j
        case 0b101111:   //"la" instruction.
            // assign the address rt = immediate address stored in machineCode;
            // first find the rt index in the register array.
            rt = (machineCode & 0x001F0000) >> 16;
            // assign the address stored in immediate field to regFile[rt];
            regFile[rt] = machineCode & 0x0000FFFF;  // get the last 16 bit as address.
            // update PCregister ???? Pay special attention to branch instructions.
            PCRegister += 4;
            if (DEBUG_CODE){   // print the hints to the user in DEBUG_MODE
                printf("Code Executed: %08X\n", machineCode);
                printf("****** PC Register is %08X ******\n", PCRegister);
            }
            break;
        // lb instruction
        case 0b100000:
            rt = (machineCode >> 16) & 0x1F;
            rs = (machineCode >> 21) & 0x1F;
            immediate = (short)(machineCode & 0xFFFF);
            regFile[rt] = (unsigned char)mem[(int)(regFile[rs] + immediate)];
            PCRegister += 4;
            break;

        // continue to all the other cases used in the program.
        // case ......:
        //lw
        case 0b100011:
            rt = (machineCode >> 16) & 0x1F;
            rs = (machineCode >> 21) & 0x1F;
            immediate = (short)(machineCode & 0xFFFF);
            regFile[rt] = read_dword(mem, regFile[rs] + immediate);
            PCRegister += 4;
            break;

        // sw instruction
        case 0b101011:
            rt = (machineCode >> 16) & 0x1F;
            rs = (machineCode >> 21) & 0x1F;
            immediate = (short)(machineCode & 0xFFFF);
            write_dword(mem, regFile[rs] + immediate, regFile[rt]);
            PCRegister += 4;
            break;

        // addi instruction
        case 0b001000:
            rt = (machineCode >> 16) & 0x1F;
            rs = (machineCode >> 21) & 0x1F;
            immediate = (short)(machineCode & 0xFFFF);
            regFile[rt] = regFile[rs] + immediate;
            PCRegister += 4;
            break;

        // add (R-type)
        case 0x00:
            funct = machineCode & 0x3F;

            rs = (machineCode >> 21) & 0x1F;
            rt = (machineCode >> 16) & 0x1F;
            rd = (machineCode >> 11) & 0x1F;

            switch (funct)
            {
                case 0x20: // ADD
                    regFile[rd] = regFile[rs] + regFile[rt];
                    break;

                default:
                    printf("Unknown R-type funct: %02X\n", funct);
                    exit(1);
            }

            PCRegister += 4;
            break;
        // bge
        case 0b000001:
        {
            rs = (machineCode >> 21) & 0x1F;
            rt = (machineCode >> 16) & 0x1F;
            immediate = (short)(machineCode & 0xFFFF);

            if (regFile[rs] >= regFile[rt])
                PCRegister = PCRegister + 4 + (immediate << 2);
            else
                PCRegister += 4;
            break;
        }

        // j instruction
        case 0b000010:
            address = machineCode & 0x03FFFFFF;

            PCRegister =
                (PCRegister & 0xF0000000) |
                (address << 2);
            break;

        // Should never go to default part when complete. Otherwise, that is a mistake.
        default:
            printf("Wrong instruction! You need to fix this instruction %02X %08X\n", opcode,  machineCode);
            system("PAUSE");
            exit(3);  // exit the program if running here.
            break;
    }
}
// Lab 8 - Step 3. Print all the 32 registers in regFile and names saved in
//         regNameTab. For example, it should print
//         $zero = 0x00000000
//         $at  = ... ... etc.
void printRegisterFiles(){
    printf("\n---- REGISTER FILE ----\n");

        for(int i = 0; i < N_REG; i++)
        {
            printf("%s = 0x%08X\n", regNameTab[i], regFile[i]);
        }
    }

 // Lab 8 - Step 4. Call function memory_dump and pass the proper parameters to dump the first 256
//          bytes from Data section.
void printDataMemoryDump(char *mem)
{
    printf("\n---- DATA MEMORY DUMP ----\n");

    // Data section starts at DATASECTION = 0x2000
    memory_dump(mem, DATASECTION, 256);
}

