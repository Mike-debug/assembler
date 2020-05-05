#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
struct Lable{
	int addr;
	char labletag[30];
};
struct Lable LableArray[100];
int Count=0;
int Address=0; 
FILE *AsmCode, *MachineCode;//汇编文件和机器码文件 
int StringToInteger(char *s){
	char *p;
	p=s;
	int i;
	int sum=0;
	if(p[0]>=0x30&&p[0]<=0x39)
		for(i=0;i<strlen(s);++i)
			sum=sum*10+p[i]-0x30;
	else
		for(i=0;i<Count;++i)
			if(strcmp(LableArray[i].labletag,p)==0){
				sum=LableArray[i].addr;
				break;
			}
	
//	puts(p);
//	printf("%d ",LableArray[i].addr);
//	puts(LableArray[i].labletag);
	return sum;
}
int OpAsmToMachine(char *AsmOp){//把操作码转换成机器码 
	int MachineOp=-1;
	//R型指令 
	char add[]="add";//0
	char sub[]="sub";//1
	char And[] ="and";//2
	char Or[]="or";//3
	char nor[]="nor";//4
	char slt[]="slt";//5
	char sll[]="sll";//6
	char srl[]="srl";//7
	char jr[]="jr";//8
	//I型指令 
	char lw[]="lw";//9
	char sw[]="sw";//10
	char addi[]="addi";//11
	char andi[]="andi";//12
	char ori[]="ori";//13
	char beq[]="beq";//14
	char bne[]="bne";//15
	//J型指令 
	char j[]="j";//16
	char jal[]="jal";//17
	//I型指令 
	char lui[]="lui";//18
	//异常指令
	char eret[]="eret";//19 
	if(strcmp(AsmOp,add)==0) 
		MachineOp=0;
	else if(strcmp(AsmOp,sub)==0)
		MachineOp=1;
	else if(strcmp(AsmOp,And)==0)
		MachineOp=2;
	else if(strcmp(AsmOp,Or)==0)
		MachineOp=3;
	else if(strcmp(AsmOp,nor)==0)
		MachineOp=4;
	else if(strcmp(AsmOp,slt)==0)
		MachineOp=5;
	else if(strcmp(AsmOp,sll)==0)
		MachineOp=6;
	else if(strcmp(AsmOp,srl)==0)
		MachineOp=7;
	else if(strcmp(AsmOp,jr)==0)
		MachineOp=8;
	else if(strcmp(AsmOp,lw)==0)
		MachineOp=9;
	else if(strcmp(AsmOp,sw)==0)
		MachineOp=10;
	else if(strcmp(AsmOp,addi)==0)
		MachineOp=11;
	else if(strcmp(AsmOp,andi)==0)
		MachineOp=12;
	else if(strcmp(AsmOp,ori)==0)
		MachineOp=13;
	else if(strcmp(AsmOp,beq)==0)
		MachineOp=14;
	else if(strcmp(AsmOp,bne)==0)
		MachineOp=15;
	else if(strcmp(AsmOp,j)==0)
		MachineOp=16;
	else if(strcmp(AsmOp,jal)==0)
		MachineOp=17;
	else if(strcmp(AsmOp,lui)==0)
		MachineOp=18;
	else if(strcmp(AsmOp,eret)==0)
		MachineOp=19;
	return MachineOp;
}
int RegAsmToMachine(char *Register){//把寄存器转换成机器码 
	int MachineReg=-1;
	char zero[]="$zero";//0
	char at[]="$at";//1
	char v0[]="$v0";//2
	char v1[]="$v1";//3
	char a0[]="$a0";//4
	char a1[]="$a1";//5
	char a2[]="$a2";//6
	char a3[]="$a3";//7
	char t0[]="$t0";//8
	char t1[]="$t1";//9
	char t2[]="$t2";//10
	char t3[]="$t3";//11
	char t4[]="$t4";//12
	char t5[]="$t5";//13
	char t6[]="$t6";//14
	char t7[]="$t7";//15
	char s0[]="$s0";//16
	char s1[]="$s1";//17
	char s2[]="$s2";//18
	char s3[]="$s3";//19
	char s4[]="$s4";//20
	char s5[]="$s5";//21
	char s6[]="$s6";//22
	char s7[]="$s7";//23
	char t8[]="$t8";//24
	char t9[]="$t9";//25
	char k0[]="$k0";//26
	char k1[]="$k1";//27
	char gp[]="$gp";//28
	char sp[]="$sp";//29
	char fp[]="$fp";//30
	char ra[]="$ra";//31

	if(strcmp(Register,zero)==0)MachineReg=0;
	else if(strcmp(Register,at)==0)MachineReg=1;
	else if(strcmp(Register,v0)==0)MachineReg=2;
	else if(strcmp(Register,v1)==0)MachineReg=3;
	else if(strcmp(Register,a0)==0)MachineReg=4;
	else if(strcmp(Register,a1)==0)MachineReg=5;
	else if(strcmp(Register,a2)==0)MachineReg=6;
	else if(strcmp(Register,a3)==0)MachineReg=7;
	else if(strcmp(Register,t0)==0)MachineReg=8;
	else if(strcmp(Register,t1)==0)MachineReg=9;
	else if(strcmp(Register,t2)==0)MachineReg=10;
	else if(strcmp(Register,t3)==0)MachineReg=11;
	else if(strcmp(Register,t4)==0)MachineReg=12;
	else if(strcmp(Register,t5)==0)MachineReg=13;
	else if(strcmp(Register,t6)==0)MachineReg=14;
	else if(strcmp(Register,t7)==0)MachineReg=15;
	else if(strcmp(Register,s0)==0)MachineReg=16;
	else if(strcmp(Register,s1)==0)MachineReg=17;
	else if(strcmp(Register,s2)==0)MachineReg=18;
	else if(strcmp(Register,s3)==0)MachineReg=19;
	else if(strcmp(Register,s4)==0)MachineReg=20;
	else if(strcmp(Register,s5)==0)MachineReg=21;
	else if(strcmp(Register,s6)==0)MachineReg=22;
	else if(strcmp(Register,s7)==0)MachineReg=23;
	else if(strcmp(Register,t8)==0)MachineReg=24;
	else if(strcmp(Register,t9)==0)MachineReg=25;
	else if(strcmp(Register,k0)==0)MachineReg=26;
	else if(strcmp(Register,k1)==0)MachineReg=27;
	else if(strcmp(Register,gp)==0)MachineReg=28;
	else if(strcmp(Register,sp)==0)MachineReg=29;
	else if(strcmp(Register,fp)==0)MachineReg=30;
	else if(strcmp(Register,ra)==0)MachineReg=31;

	return MachineReg;
}
char *IntToBit5b(int Reg){//把不超过32的数字转换成5位机器码 
	char *Bit;
	Bit=(char*)malloc(6*sizeof(char));
	Reg=(Reg<0)?(Reg+32):Reg;
	Reg%=32;
	int i=0;
	Bit[5]='\0';
	for(i=4;i>=0;--i){
		Bit[i]=Reg%2+0x30;
		Reg/=2;
	}
	return Bit;
}
char *IntToBit6b(int Reg){//把不超过64的数字转换成6位机器码 
	char *Bit;
	Bit=(char*)malloc(6*sizeof(char));
	Reg%=64;
	int i=0;
	Bit[6]='\0';
	for(i=5;i>=0;--i){
		Bit[i]=Reg%2+0x30;
		Reg/=2;
	}
	return Bit;
}
char *IntToBit16b(int Immediate){
	char *Bit;
	Bit=(char*)malloc(17*sizeof(char));
	Immediate=(Immediate<0)?(Immediate+pow(2,16)):Immediate;
	Immediate%=65536;
	int i=0;
	Bit[16]='\0';
	for(i=15;i>=0;--i){
		Bit[i]=Immediate%2+0x30;
		Immediate/=2;
	}
	return Bit;
}
char *IntToBit26b(int Immediate){
	char *Bit;
	Bit=(char*)malloc(27*sizeof(char));
	Immediate=(Immediate<0)?(Immediate+pow(2,26)):Immediate;
	Immediate%=67108864;
	int i=0;
	Bit[26]='\0';
	for(i=25;i>=0;--i){
		Bit[i]=Immediate%2+0x30;
		Immediate/=2;
	}
	return Bit;
}
char *AddInstruction(void){//Add指令 
	char *MachineInstruct;
	MachineInstruct=(char*)malloc(33*sizeof(char));
	char *rs, *rt, *rd;
	rs=(char*)malloc(6*sizeof(char));
	rt=(char*)malloc(6*sizeof(char));
	rd=(char*)malloc(6*sizeof(char));
	fscanf(AsmCode,"%s",rd);
	if(rd[1]!='z')rd[3]='\0';else rd[5]='\0';
	fgetc(AsmCode);
	fscanf(AsmCode,"%s",rs);
	if(rs[1]!='z')rs[3]='\0';else rs[5]='\0';
	fgetc(AsmCode);
	fscanf(AsmCode,"%s",rt);
	if(rt[1]!='z')rt[3]='\0';else rt[5]='\0';
	char op[]="000000\0";
	char shamt[]="00000\0";
	char func[]="100000\0";
	MachineInstruct[0]='\0';
	MachineInstruct=strcat(MachineInstruct,op);
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rs)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rt)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rd)));
	MachineInstruct=strcat(MachineInstruct,shamt);
	MachineInstruct=strcat(MachineInstruct,func);

	return MachineInstruct;
}
char *SubInstruction(void){//Sub指令 
	char *MachineInstruct;
	MachineInstruct=(char*)malloc(33*sizeof(char));
	char *rs, *rt, *rd;
	rs=(char*)malloc(6*sizeof(char));
	rt=(char*)malloc(6*sizeof(char));
	rd=(char*)malloc(6*sizeof(char));
	fscanf(AsmCode,"%s",rd);
	if(rd[1]!='z')rd[3]='\0';else rd[5]='\0';
	fgetc(AsmCode);
	fscanf(AsmCode,"%s",rs);
	if(rs[1]!='z')rs[3]='\0';else rs[5]='\0';
	fgetc(AsmCode);
	fscanf(AsmCode,"%s",rt);
	if(rt[1]!='z')rt[3]='\0';else rt[5]='\0';
	char op[]="000000\0";
	char shamt[]="00000\0";
	char func[]="100010\0";
	MachineInstruct[0]='\0';
	MachineInstruct=strcat(MachineInstruct,op);
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rs)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rt)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rd)));
	MachineInstruct=strcat(MachineInstruct,shamt);
	MachineInstruct=strcat(MachineInstruct,func);

	return MachineInstruct;
}
char *AndInstruction(void){
	char *MachineInstruct;
	MachineInstruct=(char*)malloc(33*sizeof(char));
	char *rs, *rt, *rd;
	rs=(char*)malloc(6*sizeof(char));
	rt=(char*)malloc(6*sizeof(char));
	rd=(char*)malloc(6*sizeof(char));
	fscanf(AsmCode,"%s",rd);
	if(rd[1]!='z')rd[3]='\0';else rd[5]='\0';
	fgetc(AsmCode);
	fscanf(AsmCode,"%s",rs);
	if(rs[1]!='z')rs[3]='\0';else rs[5]='\0';
	fgetc(AsmCode);
	fscanf(AsmCode,"%s",rt);
	if(rt[1]!='z')rt[3]='\0';else rt[5]='\0';
	char op[]="000000\0";
	char shamt[]="00000\0";
	char func[]="100100\0";
	MachineInstruct[0]='\0';
	MachineInstruct=strcat(MachineInstruct,op);
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rs)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rt)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rd)));
	MachineInstruct=strcat(MachineInstruct,shamt);
	MachineInstruct=strcat(MachineInstruct,func);

	return MachineInstruct;
}
char *OrInstruction(void){
	char *MachineInstruct;
	MachineInstruct=(char*)malloc(33*sizeof(char));
	char *rs, *rt, *rd;
	rs=(char*)malloc(6*sizeof(char));
	rt=(char*)malloc(6*sizeof(char));
	rd=(char*)malloc(6*sizeof(char));
	fscanf(AsmCode,"%s",rd);
	if(rd[1]!='z')rd[3]='\0';else rd[5]='\0';
	fgetc(AsmCode);
	fscanf(AsmCode,"%s",rs);
	if(rs[1]!='z')rs[3]='\0';else rs[5]='\0';
	fgetc(AsmCode);
	fscanf(AsmCode,"%s",rt);
	if(rt[1]!='z')rt[3]='\0';else rt[5]='\0';
	char op[]="000000\0";
	char shamt[]="00000\0";
	char func[]="100101\0";
	MachineInstruct[0]='\0';
	MachineInstruct=strcat(MachineInstruct,op);
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rs)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rt)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rd)));
	MachineInstruct=strcat(MachineInstruct,shamt);
	MachineInstruct=strcat(MachineInstruct,func);

	return MachineInstruct;
}
char *NorInstruction(void){
	char *MachineInstruct;
	MachineInstruct=(char*)malloc(33*sizeof(char));
	char *rs, *rt, *rd;
	rs=(char*)malloc(6*sizeof(char));
	rt=(char*)malloc(6*sizeof(char));
	rd=(char*)malloc(6*sizeof(char));
	fscanf(AsmCode,"%s",rd);
	if(rd[1]!='z')rd[3]='\0';else rd[5]='\0';
	fgetc(AsmCode);
	fscanf(AsmCode,"%s",rs);
	if(rs[1]!='z')rs[3]='\0';else rs[5]='\0';
	fgetc(AsmCode);
	fscanf(AsmCode,"%s",rt);
	if(rt[1]!='z')rt[3]='\0';else rt[5]='\0';
	char op[]="000000\0";
	char shamt[]="00000\0";
	char func[]="100111\0";
	MachineInstruct[0]='\0';
	//puts(rs);
	//puts(IntToBit5b(RegAsmToMachine(rt)));
	MachineInstruct=strcat(MachineInstruct,op);
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rs)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rt)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rd)));
	MachineInstruct=strcat(MachineInstruct,shamt);
	MachineInstruct=strcat(MachineInstruct,func);
	
	return MachineInstruct;
}
char *SltInstruction(void){
	char *MachineInstruct;
	MachineInstruct=(char*)malloc(33*sizeof(char));
	char *rs, *rt, *rd;
	rs=(char*)malloc(6*sizeof(char));
	rt=(char*)malloc(6*sizeof(char));
	rd=(char*)malloc(6*sizeof(char));
	fscanf(AsmCode,"%s",rd);
	if(rd[1]!='z')rd[3]='\0';else rd[5]='\0';
	fgetc(AsmCode);
	fscanf(AsmCode,"%s",rs);
	if(rs[1]!='z')rs[3]='\0';else rs[5]='\0';
	fgetc(AsmCode);
	fscanf(AsmCode,"%s",rt);
	if(rt[1]!='z')rt[3]='\0';else rt[5]='\0';
	char op[]="000000\0";
	char shamt[]="00000\0";
	char func[]="101010\0";
	MachineInstruct[0]='\0';
	MachineInstruct=strcat(MachineInstruct,op);
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rs)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rt)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rd)));
	MachineInstruct=strcat(MachineInstruct,shamt);
	MachineInstruct=strcat(MachineInstruct,func);

	return MachineInstruct;
}
char *SllInstruction(void){//Sll指令 
	char *MachineInstruct;
	MachineInstruct=(char*)malloc(33*sizeof(char));
	char Bitrs[]="00000\0";
	char *rt, *rd;
	rt=(char*)malloc(6*sizeof(char));
	rd=(char*)malloc(6*sizeof(char));
	fscanf(AsmCode,"%s",rd);
	if(rd[1]!='z')rd[3]='\0';else rd[5]='\0';
	fgetc(AsmCode);
	fscanf(AsmCode,"%s",rt);
	if(rt[1]!='z')rt[3]='\0';else rt[5]='\0';
	char op[]="000000\0";
	int shamt;
	char func[]="000000\0";
	MachineInstruct[0]='\0';
	fscanf(AsmCode,"%d",&shamt);
	MachineInstruct=strcat(MachineInstruct,op);
	MachineInstruct=strcat(MachineInstruct,Bitrs);
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rt)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rd)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(shamt));
	MachineInstruct=strcat(MachineInstruct,func);

	return MachineInstruct;
}
char *SrlInstruction(void){//Srl指令 
	char *MachineInstruct;
	MachineInstruct=(char*)malloc(33*sizeof(char));
	char Bitrs[]="00000\0";
	char *rt, *rd;
	rt=(char*)malloc(6*sizeof(char));
	rd=(char*)malloc(6*sizeof(char));
	fscanf(AsmCode,"%s",rd);
	if(rd[1]!='z')rd[3]='\0';else rd[5]='\0';
	fgetc(AsmCode);
	fscanf(AsmCode,"%s",rt);
	if(rt[1]!='z')rt[3]='\0';else rt[5]='\0';
	char op[]="000000\0";
	int shamt;
	char func[]="000010\0";
	MachineInstruct[0]='\0';
	fscanf(AsmCode,"%d",&shamt);
	MachineInstruct=strcat(MachineInstruct,op);
	MachineInstruct=strcat(MachineInstruct,Bitrs);
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rt)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rd)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(shamt));
	MachineInstruct=strcat(MachineInstruct,func);

	return MachineInstruct;
}
char *JrInstruction(void){
	char *MachineInstruct;
	MachineInstruct=(char*)malloc(33*sizeof(char));
	char *rs;
	rs=(char*)malloc(6*sizeof(char));
	char Bitrt[]="00000\0";
	char Bitrd[]="00000\0";
	fscanf(AsmCode,"%s",rs);
	if(rs[1]!='z')rs[3]='\0';else rs[5]='\0';
	char op[]="000000\0";
	char shamt[]="00000\0";
	char func[]="001000\0";
	MachineInstruct[0]='\0';
	MachineInstruct=strcat(MachineInstruct,op);
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rs)));
	MachineInstruct=strcat(MachineInstruct,Bitrt);
	MachineInstruct=strcat(MachineInstruct,Bitrd);
	MachineInstruct=strcat(MachineInstruct,shamt);
	MachineInstruct=strcat(MachineInstruct,func);

	return MachineInstruct;
}
char *LwInstruction(void){
	char *MachineInstruct;
	MachineInstruct=(char*)malloc(33*sizeof(char));
	char *rs, *rt;
	rs=(char*)malloc(6*sizeof(char));
	rt=(char*)malloc(6*sizeof(char));
	fscanf(AsmCode,"%s",rt);
	if(rt[1]!='z')rt[3]='\0';else rt[5]='\0';
	int Immediate;
	fscanf(AsmCode,"%d",&Immediate);
	fgetc(AsmCode);
	fscanf(AsmCode,"%s",rs);
	if(rs[1]!='z')rs[3]='\0';else rs[5]='\0';
	char op[]="100011\0";
	MachineInstruct[0]='\0';
	MachineInstruct=strcat(MachineInstruct,op);
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rs)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rt)));
	MachineInstruct=strcat(MachineInstruct,IntToBit16b(Immediate));
	
	return MachineInstruct;
}
char *SwInstruction(void){
	char *MachineInstruct;
	MachineInstruct=(char*)malloc(33*sizeof(char));
	char *rs, *rt;
	rs=(char*)malloc(6*sizeof(char));
	rt=(char*)malloc(6*sizeof(char));
	fscanf(AsmCode,"%s",rt);
	if(rt[1]!='z')rt[3]='\0';else rt[5]='\0';
	int Immediate;
	fscanf(AsmCode,"%d",&Immediate);
	fgetc(AsmCode);
	fscanf(AsmCode,"%s",rs);
	if(rs[1]!='z')rs[3]='\0';else rs[5]='\0';
	char op[]="101011\0";
	MachineInstruct[0]='\0';
	MachineInstruct=strcat(MachineInstruct,op);
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rs)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rt)));
	MachineInstruct=strcat(MachineInstruct,IntToBit16b(Immediate));
	
	return MachineInstruct;
}
char *AddiInstruction(void){
	char *MachineInstruct;
	MachineInstruct=(char*)malloc(33*sizeof(char));
	char *rs, *rt;
	rs=(char*)malloc(6*sizeof(char));
	rt=(char*)malloc(6*sizeof(char));
	fscanf(AsmCode,"%s",rt);
	if(rt[1]!='z')rt[3]='\0';else rt[5]='\0';
	fgetc(AsmCode);
	fscanf(AsmCode,"%s",rs);
	if(rs[1]!='z')rs[3]='\0';else rs[5]='\0';
	int Immediate;
	fscanf(AsmCode,"%d",&Immediate);
	char op[]="001000\0";
	MachineInstruct[0]='\0';
	MachineInstruct=strcat(MachineInstruct,op);
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rs)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rt)));
	MachineInstruct=strcat(MachineInstruct,IntToBit16b(Immediate));
	
	return MachineInstruct;
}
char *AndiInstruction(void){
	char *MachineInstruct;
	MachineInstruct=(char*)malloc(33*sizeof(char));
	char *rs, *rt;
	rs=(char*)malloc(6*sizeof(char));
	rt=(char*)malloc(6*sizeof(char));
	fscanf(AsmCode,"%s",rt);
	if(rt[1]!='z')rt[3]='\0';else rt[5]='\0';
	fgetc(AsmCode);
	fscanf(AsmCode,"%s",rs);
	if(rs[1]!='z')rs[3]='\0';else rs[5]='\0';
	int Immediate;
	fscanf(AsmCode,"%d",&Immediate);
	char op[]="001100\0";
	MachineInstruct[0]='\0';
	MachineInstruct=strcat(MachineInstruct,op);
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rs)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rt)));
	MachineInstruct=strcat(MachineInstruct,IntToBit16b(Immediate));
	
	return MachineInstruct;
}
char *OriInstruction(void){
	char *MachineInstruct;
	MachineInstruct=(char*)malloc(33*sizeof(char));
	char *rs, *rt;
	rs=(char*)malloc(6*sizeof(char));
	rt=(char*)malloc(6*sizeof(char));
	fscanf(AsmCode,"%s",rt);
	if(rt[1]!='z')rt[3]='\0';else rt[5]='\0';
	fgetc(AsmCode);
	fscanf(AsmCode,"%s",rs);
	if(rs[1]!='z')rs[3]='\0';else rs[5]='\0';
	int Immediate;
	fscanf(AsmCode,"%d",&Immediate);
	char op[]="001101\0";
	MachineInstruct[0]='\0';
	MachineInstruct=strcat(MachineInstruct,op);
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rs)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rt)));
	MachineInstruct=strcat(MachineInstruct,IntToBit16b(Immediate));
	
	return MachineInstruct;
}
char *BeqInstruction(void){
	char *MachineInstruct;
	MachineInstruct=(char*)malloc(33*sizeof(char));
	char *rs, *rt;
	rs=(char*)malloc(6*sizeof(char));
	rt=(char*)malloc(6*sizeof(char));
	fscanf(AsmCode,"%s",rt);
	if(rt[1]!='z')rt[3]='\0';else rt[5]='\0';
	fgetc(AsmCode);
	fscanf(AsmCode,"%s",rs);
	if(rs[1]!='z')rs[3]='\0';else rs[5]='\0';
	char *Immediate;
	Immediate=(char*)malloc(30*sizeof(char));
	fscanf(AsmCode,"%s",Immediate);
	char op[]="000100\0";
	MachineInstruct[0]='\0';
	MachineInstruct=strcat(MachineInstruct,op);
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rs)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rt)));
	MachineInstruct=strcat(MachineInstruct,IntToBit16b(StringToInteger(Immediate)-1-Address));
	
	return MachineInstruct;
}
char *BneInstruction(void){
	char *MachineInstruct;
	MachineInstruct=(char*)malloc(33*sizeof(char));
	char *rs, *rt;
	rs=(char*)malloc(6*sizeof(char));
	rt=(char*)malloc(6*sizeof(char));
	fscanf(AsmCode,"%s",rt);
	if(rt[1]!='z')rt[3]='\0';else rt[5]='\0';
	fgetc(AsmCode);
	fscanf(AsmCode,"%s",rs);
	if(rs[1]!='z')rs[3]='\0';else rs[5]='\0';
	char *Immediate;
	Immediate=(char*)malloc(30*sizeof(char));
	fscanf(AsmCode,"%s",Immediate);
	char op[]="000101\0";
	MachineInstruct[0]='\0';
	MachineInstruct=strcat(MachineInstruct,op);
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rs)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rt)));
	MachineInstruct=strcat(MachineInstruct,IntToBit16b(StringToInteger(Immediate)-1-Address));
	
	return MachineInstruct;
}
char *JInstruction(void){
	char *MachineInstruct;
	MachineInstruct=(char*)malloc(33*sizeof(char));
	char *Immediate;
	Immediate=(char*)malloc(30*sizeof(char));
	fscanf(AsmCode,"%s",Immediate);
	char op[]="000010\0";
	MachineInstruct[0]='\0';
	MachineInstruct=strcat(MachineInstruct,op);
//	puts(Immediate);
//	printf("%d\n",StringToInteger(Immediate));
	MachineInstruct=strcat(MachineInstruct,IntToBit26b(StringToInteger(Immediate)));
	
	return MachineInstruct;
}
char *JalInstruction(void){
	char *MachineInstruct;
	MachineInstruct=(char*)malloc(33*sizeof(char));
	char *Immediate;
	Immediate=(char*)malloc(30*sizeof(char));
	fscanf(AsmCode,"%s",Immediate);
	char op[]="000011\0";
	MachineInstruct[0]='\0';
	MachineInstruct=strcat(MachineInstruct,op);
	MachineInstruct=strcat(MachineInstruct,IntToBit26b(StringToInteger(Immediate)));
	
	return MachineInstruct;
}
char *LuiInstruction(void){
	char *MachineInstruct;
	MachineInstruct=(char*)malloc(33*sizeof(char));
	char *rt;
	//rs=(char*)malloc(6*sizeof(char));
	rt=(char*)malloc(6*sizeof(char));
	fscanf(AsmCode,"%s",rt);
	if(rt[1]!='z')rt[3]='\0';else rt[5]='\0';
	//fgetc(AsmCode);
	char rs[]="$zero\0";
	//fscanf(AsmCode,"%s",rs);
	//if(rs[1]!='z')rs[3]='\0';else rs[5]='\0';
	char *Immediate;
	Immediate=(char*)malloc(30*sizeof(char));
	fscanf(AsmCode,"%s",Immediate);
	char op[]="001111\0";
	MachineInstruct[0]='\0';
	MachineInstruct=strcat(MachineInstruct,op);
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rs)));
	MachineInstruct=strcat(MachineInstruct,IntToBit5b(RegAsmToMachine(rt)));
	MachineInstruct=strcat(MachineInstruct,IntToBit16b(StringToInteger(Immediate)));
	
	return MachineInstruct;
}
char *EretInstruction(void){
	char *MachineInstruct;
	int i;
	MachineInstruct=(char*)malloc(33*sizeof(char));
	for(i=0;i<33;++i)MachineInstruct[i]='0';
	MachineInstruct[1]='1';
	MachineInstruct[6]='1';
	MachineInstruct[27]='1';
	MachineInstruct[28]='1';
	MachineInstruct[32]='\0';
	
	return MachineInstruct;
}
void PrintToMachineFile(char *MachineInstruction){
	char *p=MachineInstruction;
//	puts(p);
	int i=0;
	int hex=0x0;
	while(p[i]!='\0'){
		hex=hex*2+(p[i]-0x30);
		if(i%4==3){
			fprintf(MachineCode,"%x",hex);
			hex=0;
		}
		i++;
	} 
	fputs(",\n",MachineCode);
	return;
}
void ReadAsmToMachine(int DecOpCode) {
	char *MachineInstruction;//一条二进制机器指令 
	MachineInstruction=(char *)malloc(33*sizeof(char));
	switch(DecOpCode){
		case 0:
			MachineInstruction=AddInstruction();
			PrintToMachineFile(MachineInstruction);
			break;
		case 1:
			MachineInstruction=SubInstruction();
			PrintToMachineFile(MachineInstruction);
			break;
		case 2:
			MachineInstruction=AndInstruction();
			PrintToMachineFile(MachineInstruction);
			break;
		case 3:
			MachineInstruction=OrInstruction();
			PrintToMachineFile(MachineInstruction);
			break;
		case 4:
			MachineInstruction=NorInstruction();
			PrintToMachineFile(MachineInstruction);
			break;
		case 5:
			MachineInstruction=SltInstruction();
			PrintToMachineFile(MachineInstruction);
			break;
		case 6:
			MachineInstruction=SllInstruction();
			PrintToMachineFile(MachineInstruction);
			break;
		case 7:
			MachineInstruction=SrlInstruction();
			PrintToMachineFile(MachineInstruction);
			break;
		case 8:
			MachineInstruction=JrInstruction();
			PrintToMachineFile(MachineInstruction);
			break;
		case 9:
			MachineInstruction=LwInstruction();
			PrintToMachineFile(MachineInstruction);
			break;
		case 10:
			MachineInstruction=SwInstruction();
			PrintToMachineFile(MachineInstruction);
			break;
		case 11:
			MachineInstruction=AddiInstruction();
			PrintToMachineFile(MachineInstruction);
			break;
		case 12:
			MachineInstruction=AndiInstruction();
			PrintToMachineFile(MachineInstruction);
			break;
		case 13:
			MachineInstruction=OriInstruction();
			PrintToMachineFile(MachineInstruction);
			break;
		case 14:
			MachineInstruction=BeqInstruction();
			PrintToMachineFile(MachineInstruction);
			break;
		case 15:
			MachineInstruction=BneInstruction();
			PrintToMachineFile(MachineInstruction);
			break;
		case 16:
			MachineInstruction=JInstruction();
			PrintToMachineFile(MachineInstruction);
			break;
		case 17:
			MachineInstruction=JalInstruction();
			PrintToMachineFile(MachineInstruction);
			break;
		case 18:
			MachineInstruction=LuiInstruction();
			PrintToMachineFile(MachineInstruction);
			break;
		case 19:
			MachineInstruction=EretInstruction();
			PrintToMachineFile(MachineInstruction);
			break;
		default: break; 
	}
	return;
}
int main(void) {
	if((AsmCode=fopen("Asm.txt","r"))==NULL) {
		printf("Cannot open the source file!\n");
		exit(0);
	}
	char *Tmp;
	Tmp=(char *)malloc(100*sizeof(char));
	int address=0;
	while(!feof(AsmCode)){
		fscanf(AsmCode,"%s",Tmp);
		if(OpAsmToMachine(Tmp)>=0)
			address=address+1;
		else if(Tmp[strlen(Tmp)-1]==':'){
			//puts(Tmp);
			Tmp[strlen(Tmp)-1]='\0';
			LableArray[Count].addr=address;
			strcpy(LableArray[Count].labletag,Tmp);
//			printf("%d ",Count);
//			puts(LableArray[Count].labletag);
			++Count;
		}
	}
	if(fclose(AsmCode)){
		printf("Cannot close the source file!\n");
		exit(0);
	}
//	char shiyan[30]="start";
//	printf("%d\n",StringToInteger(shiyan));
//	for(int i=0;i<Count;i++){
//		printf("%d ",LableArray[i].addr);
//		puts(LableArray[i].labletag);
//	}
	rewind(AsmCode);
	if((AsmCode=fopen("Asm.txt","r"))==NULL) {
		printf("Cannot open the source file!\n");
		exit(0);
	}
	if((MachineCode=fopen("MachineCode16b.txt","w"))==NULL){
		printf("Cannot open the destination file!\n");
		exit(0);
	}
	fprintf(MachineCode,";cpu_IO_test1.asm\nmemory_initialization_radix=16;\nmemory_initialization_vector=\n");
	int DecOpCode;//十进制操作码 
	char *AsmOp;//汇编操作码 
	char *AsmRegister;//汇编寄存器 
	AsmOp=(char *)malloc(10*sizeof(char));
	AsmRegister=(char *)malloc(5*sizeof(char));
	while(!feof(AsmCode)){
		fscanf(AsmCode,"%s",AsmOp);
		DecOpCode=OpAsmToMachine(AsmOp);
//		printf("%d ",DecOpCode);
		if(DecOpCode>=0){
			ReadAsmToMachine(DecOpCode);
			++Address;
		}
		fgetc(AsmCode);
	}
	free(AsmRegister);
	free(AsmOp);
	if(fclose(MachineCode)){
		printf("Cannot close the destination file!\n");
		exit(0);
	}
	if(fclose(AsmCode)){
		printf("Cannot close the source file!\n");
		exit(0);
	}
	return 0;
}

