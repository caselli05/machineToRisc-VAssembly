#include <bits/stdc++.h>

// using namespace std;

std::string getBinary();
std::string getHex();
std::string hexToBinary(std::string hexDigits);
int strToDec(std::string s);
void typeI(std::string binaryNumber, std::string* imm, std::string* rs1, std::string* funct3, std::string* rd);
void typeR(std::string binaryNumber, std::string* funct7, std::string* rs2, std::string* rs1, std::string* funct3, std::string* rd);
void typeU(std::string binaryNumber, std::string* imm, std::string* rd);
void typeB(std::string binaryNumber, std::string* imm, std::string* rs2, std::string* rs1, std::string* funct3);
void typeS(std::string binatyNumber, std::string* imm, std::string* rs2, std::string* rs1, std::string* funct3);
void typeJ(std::string binaryNumber, std::string* imm, std::string* rd);
std::string binaryToRegister(std::string r);

int main(void){
    while(1){
        int n;
        std::cout << "[0]Exit [1]Binary [2]Hexa\n";
        std::cin >> n;
        std::string binaryDigits;
        if(n == 1){
            binaryDigits = getBinary();
        }else if(n == 2){
            binaryDigits = hexToBinary(getHex());
        }else{
            break;
        }

        std::string opcode = binaryDigits.substr(25,7);
        // tipo-i
        if(opcode.compare("0000011") == 0){
            std::string imm, funct3, rs1, rd;
            typeI(binaryDigits, &imm, &rs1, &funct3, &rd);
            if(funct3.compare("000") == 0){
                std::cout << "lb ";
            }else if(funct3.compare("001") == 0){
                std::cout << "lh ";
            }else if(funct3.compare("010") == 0){
                std::cout << "lw ";
            }else if(funct3.compare("100") == 0){
                std::cout << "lbu ";
            }else if(funct3.compare("101") == 0){
                std::cout << "lhu";
            }else{
                std::cout << "INVALID EXPRESSION\n";
                continue;
            }
            std::cout << binaryToRegister(rd) << ", ";
            std::cout << strToDec(imm);
            std::cout << "(" << binaryToRegister(rs1) << ")\n";

        }else if(opcode.compare("0010011") == 0){
            std::string imm, funct3, rs1, rd;
            typeI(binaryDigits, &imm, &rs1, &funct3, &rd);
            if(funct3.compare("000") == 0){
                std::cout << "addi ";
            }else if(funct3.compare("001") == 0){
                std::cout << "slli ";
                std::cout << binaryToRegister(rd) << ", ";
                std::cout << binaryToRegister(rs1) << ", ";
                std::cout << strToDec(('0'+imm.substr(7,5))) << std::endl;
                continue;
            }else if(funct3.compare("010") == 0){
                std::cout << "slti ";
            }else if(funct3.compare("011") == 0){
                std::cout << "sltiu ";
            }else if(funct3.compare("100") == 0){
                std::cout << "xori ";
            }else if(funct3.compare("101") == 0){
                if(binaryDigits.substr(0,7).compare("0000000") == 0){
                    std::cout << "srli ";
                }else{
                    std::cout << "srai ";
                }
                std::cout << binaryToRegister(rd) << ", ";
                std::cout << binaryToRegister(rs1) << ", ";
                std::cout << strToDec(('0'+imm.substr(7,5))) << std::endl;       
                continue;
            }else if(funct3.compare("110") == 0){
                std::cout << "ori ";
            }else if(funct3.compare("111") == 0){
                std::cout << "andi ";
            }
            else{
                std::cout << "INVALID EXPRESSION\n";
                continue;
            }
            std::cout << binaryToRegister(rd) << ", ";
            std::cout << binaryToRegister(rs1) << ", ";
            std::cout << strToDec(imm) << std::endl;

        }else if(opcode.compare("1100111") == 0){
            std::string imm, funct3, rs1, rd;
            typeI(binaryDigits, &imm, &rs1, &funct3, &rd);
            if(funct3.compare("000") == 0){
                std::cout << "jalr ";
            }else{
                std::cout << "INVALID EXPRESSION\n";
                continue;
            }
            std::cout << binaryToRegister(rd) << ", ";
            std::cout << binaryToRegister(rs1) << ", ";
            std::cout << strToDec(imm) << std::endl;

        }else if(opcode.compare("1110011") == 0){
            std::string imm, funct3, rs1, rd;
            typeI(binaryDigits, &imm, &rs1, &funct3, &rd);
            if(funct3.compare("000") == 0){
                std::cout << "ecall";
                continue;
            }else if(funct3.compare("001") == 0){
                std::cout << "csrrw ";
                imm = rs1;
            }else if(funct3.compare("010") == 0){
                std::cout << "csrrs ";
                imm = rs1;
            }else if(funct3.compare("011") == 0){
                std::cout << "csrrc ";
                imm = rs1;
            }else if(funct3.compare("101") == 0){
                std::cout << "csrrwi ";
            }else if(funct3.compare("110") == 0){
                std::cout << "csrrsi ";
            }else if(funct3.compare("111") == 0){
                std::cout << "csrrci ";
            }else{
                std::cout << "INVALID EXPRESSION\n";
                continue;
            }
            std::cout << binaryToRegister(rd) << ", ";
            std::cout << "CSR, ";
            std::cout << strToDec(imm) << std::endl;          
        }else if(opcode.compare("0000111") == 0){
            std::string imm, funct3, rs1, rd;
            typeI(binaryDigits, &imm, &rs1, &funct3, &rd);
            if(funct3.compare("010") == 0){
                std::cout << "flw ";
            }else{
                std::cout << "INVALID EXPRESSION\n";
                continue;
            }
            std::cout << rd << ", ";
            std::cout << strToDec(imm) << "(" << binaryToRegister(rs1) << ")" << std::endl;
        }
        //tipo-r
        else if(opcode.compare("0110011") == 0){
            std::string funct7, rs2, rs1, funct3, rd;
            typeR(binaryDigits, &funct7, &rs2, &rs1, &funct3, &rd);
            if(funct3.compare("000") == 0){
                if(funct7.compare("0000000") == 0){
                    std::cout << "add ";
                }else if(funct7.compare("0100000") == 0){
                    std::cout << "sub ";
                }else if(funct7.compare("0000001") == 0){
                    std::cout << "mul ";
                }else{
                    std::cout << "INVALID EXPRESSION\n";
                    continue;
                }
            }else if((funct3.compare("001") == 0)){
                if(funct7.compare("0000000") == 0){
                    std::cout << "sll ";
                }else if(funct7.compare("0000001") == 0){
                    std::cout << "mulh ";
                }else{
                    std::cout << "INVALID EXPRESSION\n";
                    continue;
                }
            }else if((funct3.compare("010") == 0)){
                if(funct7.compare("0000000") == 0){
                    std::cout << "slt ";
                }else if(funct7.compare("0000001") == 0){
                    std::cout << "mulhsu ";
                }
            }else if((funct3.compare("011") == 0)){
                if(funct7.compare("0000000") == 0){
                    std::cout << "sltu ";
                }else if(funct7.compare("0000001") == 0){
                    std::cout << "mulhu ";
                }
            }else if((funct3.compare("100") == 0)){
                if(funct7.compare("0000000") == 0){
                    std::cout << "xor ";
                }else if(funct7.compare("0000001") == 0){
                    std::cout << "div ";
                }
            }else if(funct3.compare("101") == 0){
                if(funct7.compare("0000000") == 0){
                    std::cout << "srl ";
                }else if(funct7.compare("0000001") == 0){
                    std::cout << "divu ";
                }else if(funct7.compare("0100000") == 0){
                    std::cout << "sra ";
                }else{
                    std::cout << "INVALID EXPRESSION\n";
                }
            }else if((funct3.compare("110") == 0)){
                if(funct7.compare("0000000") == 0){
                    std::cout << "or ";
                }else if(funct7.compare("0000001") == 0){
                    std::cout << "rem ";
                }
            }else if((funct3.compare("111") == 0)){
                if(funct7.compare("0000000") == 0){
                    std::cout << "and ";
                }else if(funct7.compare("0000001") == 0){
                    std::cout << "remu ";
                }
            }else{
                std::cout << "INVALID EXPRESSION\n";
            }
            std::cout << binaryToRegister(rd) << ", " << binaryToRegister(rs1) << ", " << binaryToRegister(rs2) << std::endl;
        }
        // tipo-U
        else if(opcode.compare("0010111") == 0){
            std::string imm, rd;
            typeU(binaryDigits, &imm, &rd);
            std::cout << "auipc " << binaryToRegister(rd) << ", " << strToDec(imm) << std::endl;
        }else if(opcode.compare("0110111") == 0){
            std::string imm, rd;
            typeU(binaryDigits, &imm, &rd);
            std::cout << "lui " << binaryToRegister(rd) << ", " << strToDec(imm) << std::endl;
        }
        // tipo-B
        else if(opcode.compare("1100011") == 0){
            std::string imm, rs2, rs1, funct3;
            typeB(binaryDigits, &imm, &rs2, &rs1, &funct3);
            if(funct3.compare("000") == 0){
                std::cout << "beq ";
            }else if(funct3.compare("001") == 0){
                std::cout << "bne ";
            }else if(funct3.compare("100") == 0){
                std::cout << "blt ";
            }else if(funct3.compare("101") == 0){
                std::cout << "bge ";
            }else if(funct3.compare("110") == 0){
                std::cout << "bltu ";
            }else if(funct3.compare("111") == 0){
                std::cout << "bgeu ";
            }else{
                std::cout << "INVALID\n";
            }
            std::cout << binaryToRegister(rs1) << ", " << binaryToRegister(rs2) << ", " << strToDec(imm) << std::endl; 
        }
        //tipe S
        else if(opcode.compare("0100011") == 0){
            std::string imm, rs2, rs1, funct3;
            typeS(binaryDigits, &imm, &rs2, &rs1, &funct3);
            if(funct3.compare("000") == 0){
                std::cout << "sb ";
            }else if(funct3.compare("001") == 0){
                std::cout << "sh ";
            }else if(funct3.compare("010") == 0){
                std::cout << "sw ";
            }else{
                std::cout << "INVALID\n";
                continue;
            }
            std::cout << binaryToRegister(rs2) << ", " << strToDec(imm) << "(" << binaryToRegister(rs1) << ")\n";
        }
        // tipo-J
        else if(opcode.compare("1101111") == 0){
            std::string imm, rd;
            typeJ(binaryDigits, &imm, &rd);
            std::cout << "jal " << binaryToRegister(rd) << ", " << strToDec(imm) << std::endl;
        }
    }
    
    return 0;
}


std::string getBinary(){
    std::cout << "Enter a binary number:\n 0b";
    std::string s;
    std::cin >> s;
    if(s.size() != 32){
        std::cout << "Must have 32 digits\n";
        return getBinary();
    }
    for(int i = 0; i < 32; i++){
        if((s[i] != '0') && (s[i] != '1')){
            std::cout << "Enter a valid binary number\n";
            return getBinary();
        }
    }
    return s;
}


std::string getHex(){
    std::cout << "Enter a hex number:\n 0x";
    std::string s;
    std::cin >> s;
    if(s.size() != 8){
        std::cout << "Must have 8 digits\n";
        return getHex();
    }
    for(int i = 0; i < 8; i++){
        if(!(('0' <= s[i]) && (s[i] <= '9')) && !(('A' <= toupper(s[i])) && (toupper(s[i]) <= 'F'))){
            std::cout << "Enter a valid binary number\n";
            return getHex();
        }
    }
    return s;
}


std::string hexToBinary(std::string hexDigits){
    std::string s = "";
    std::string hexToBin[16] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
    for(int i = 0; i < 8; i++){
        if(!isalpha(hexDigits[i])){
            s = s + hexToBin[hexDigits[i]-'0'];
        }else{
            s = s + hexToBin[toupper(hexDigits[i])-'A'+10];
        }
    }
    return s;
}


int strToDec(std::string s){
    bool invert = 0;
    if(s[0] == '1'){
        invert = 1;
        for(int i = 0, k = s.size(); i < k; i++){
            if(s[i] == '1'){
                s[i] = '0';
            }else{
                s[i] = '1';
            }
        }
        s[s.size()-1] += 1;
        for(int i = s.size()-1; i > 0; i--){
            if(s[i] == '2'){
                s[i] = '0';
                s[i-1] += 1;
            }
        }
    }
    int value = 0;
    for(int i = 0, k = s.size(); i < k; i++){
        int p = pow(2, k-1-i);
        value += ((s[i]-'0')*p);
    }
    if(invert){
        return (-1)*value;
    }
    return value;
}


void typeI(std::string binaryNumber, std::string* imm, std::string* rs1, std::string* funct3, std::string* rd){
    *imm = binaryNumber.substr(0,12);
    *rs1 = binaryNumber.substr(12,5);
    *funct3 = binaryNumber.substr(17,3);
    *rd = binaryNumber.substr(20,5);
    return;
}


void typeR(std::string binaryNumber, std::string* funct7, std::string* rs2, std::string* rs1, std::string* funct3, std::string* rd){
    *funct7 = binaryNumber.substr(0,7);
    *rs2 = binaryNumber.substr(7,5);
    *rs1 = binaryNumber.substr(12,5);
    *funct3 = binaryNumber.substr(17,3);
    *rd = binaryNumber.substr(20,5);
    return;
}


void typeU(std::string binaryNumber, std::string* imm, std::string* rd){
    *imm = binaryNumber.substr(0,20);
    *rd = binaryNumber.substr(20,5);
    return;
}


void typeB(std::string binaryNumber, std::string* imm, std::string* rs2, std::string* rs1, std::string* funct3){
    *imm = binaryNumber[0];
    *imm = *imm + binaryNumber[11];
    *imm = *imm + binaryNumber.substr(1,6);
    *imm = *imm + binaryNumber.substr(20,4);
    *imm = *imm + "0";
    *rs2 = binaryNumber.substr(7,5);
    *rs1 = binaryNumber.substr(12,5);
    *funct3 = binaryNumber.substr(17,3);
}


void typeS(std::string binatyNumber, std::string* imm, std::string* rs2, std::string* rs1, std::string* funct3){
    *imm = binatyNumber.substr(0,7);
    *imm = *imm + binatyNumber.substr(20,5);
    *rs2 = binatyNumber.substr(7,5);
    *rs1 = binatyNumber.substr(12,5);
    *funct3 = binatyNumber.substr(17,3);
    return;
}


void typeJ(std::string binaryNumber, std::string* imm, std::string* rd){
    *imm = binaryNumber[0];
    *imm = *imm + binaryNumber.substr(12,8);
    *imm = *imm + binaryNumber[11];
    *imm = *imm + binaryNumber.substr(1,10);
    *imm = *imm + '0';
    *rd = binaryNumber.substr(20,5);
    return;
}


std::string binaryToRegister(std::string r){
    int decimal = 0;
    for(int i = 0; i < 5; i++){
        int p = pow(2, 4-i);
        decimal += ((r[i]-'0')*p);
    }

    std::string registers[32] = {"zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
    "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};
    
    return registers[decimal];
}
