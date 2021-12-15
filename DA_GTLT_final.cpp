#include<iostream>
#include<fstream>
#include<conio.h>
#include<string.h>
#include<math.h>
using namespace std;
struct Matrix{
    int n;
    double data[101][101];
};
void inputFile(char f[]){
    printf("Nhap ten file: ");
    cin.getline(f,30);
    strcat(f,".txt");
}
bool checkFile(char f[]){
    FILE *i;
    if(strlen(f)==4){
        printf("Vui long nhap ten file!");
        getch();
        printf("\r"); 
        printf("\x1b[2K");
        printf("\x1b[1F");
        printf("\x1b[2K");
        return false;
    }
    i=fopen(f,"r");
    if (!i ){
        printf("Khong ton tai file: %s!",f);
        getch();
        printf("\r");
        printf("\x1b[2K");
        printf("\x1b[1F");
        printf("\x1b[2K");
        return false;
    }else{
        int c=fgetc(i);
        if (EOF==c) {
            printf("File %s rong!",f);
            getch();
            printf("\r");
            printf("\x1b[2K");
            printf("\x1b[1F");
            printf("\x1b[2K");
            return false;
        } 
        else{
            ungetc(c, i);
        }
    
    }
    fclose(i);
    return true;
}
void saveMatrixToFile(Matrix A,string w){
    FILE *o;
    char fo[]="result.txt";
    o=fopen(fo,"a+");
    fprintf(o,"%s",&w[0]);
    fprintf(o,"Kich thuoc ma tran: %d\n",A.n);
    for(int i=0;i<A.n;i++)
        fprintf(o,"________");
    fprintf(o,"_\n");
    for(int i=0;i<A.n;i++){
        for(int j=0;j<A.n;j++){
            fprintf(o,"|%6.2f ",A.data[i][j]);
        }
        fprintf(o,"|\n");
        for(int j=0;j<A.n;j++)
            fprintf(o,"|_______");
        fprintf(o,"|\n");
    
    }
    fprintf(o,"\n");
    fclose(o);
}
void save2MatrixToFile(Matrix A,Matrix B,string w){
    FILE *o;
    string fo="result.txt";
    int line,lineLength=0;
    if(A.n<2){
        line=2;
        lineLength=-2;
    }
    else if(A.n==2) line=2;
    else {
        line=2;
        lineLength=2*(A.n-2);
    }
    o=fopen(&fo[0],"a+");
    fprintf(o,"%s",&w[0]);
    fprintf(o,"Ma tran goc:      ");
    for(int k=0;k<line+lineLength;k++)fprintf(o,"\t"); 
    fprintf(o,"\t\tMa tran sau khi doi:\n");
    fprintf(o,"Kich thuoc ma tran: %d",A.n);
    for(int k=0;k<line+lineLength;k++)fprintf(o,"\t");
    fprintf(o,"\tKich thuoc ma tran: %d\n",B.n);
    
    for(int i=0;i<A.n;i++)
        fprintf(o,"________");
    fprintf(o,"_");
    for(int k=0;k<line;k++)fprintf(o,"\t");
    fprintf(o,"\t\t");
    for(int i=0;i<B.n;i++)
        fprintf(o,"________");
    fprintf(o,"_\n");
    
    for(int i=0;i<A.n;i++){
        for(int j=0;j<A.n;j++){
            fprintf(o,"|%6.2f ",A.data[i][j]);
        }
        fprintf(o,"|");
        if(i<B.n){
            for(int k=0;k<line;k++)fprintf(o,"\t");
            fprintf(o,"\t\t");
            for(int j=0;j<B.n;j++){
                fprintf(o,"|%6.2f ",B.data[i][j]);
            }
            fprintf(o,"|");
        
        }
        fprintf(o,"\n");
        for(int j=0;j<A.n;j++)
            fprintf(o,"|_______");
        fprintf(o,"|");
        if(i<B.n){
            for(int k=0;k<line;k++)fprintf(o,"\t");
            fprintf(o,"\t\t");
            for(int j=0;j<B.n;j++)
                fprintf(o,"|_______");
            fprintf(o,"|");
        }
        fprintf(o,"\n");
    }
    fprintf(o,"\n");
    fclose(o);
}
void saveFile(string w,string ans){
    FILE *o;
    string fo="result.txt";
    o=fopen(&fo[0],"a+");
    fprintf(o,"%s%s",&w[0],&ans[0]);
    fclose(o);
}
bool isDigit(char c){
    if(c>='0'&&c<='9')
        return true;
    else
        return false;
}
bool checkMatrix(FILE *file,int &li){
        li=0;
        int total = 0 ,line=1,once=1;
        bool state=false,error=true;
        char st[200];
        while(feof(file)==0)
            while(fgets(st,200,file))
                total++;
        rewind(file);
        while(feof(file)==0){
            int index=0,cnt=0,tmponce=once;
            fgets(&st[0],200,file);
            while(cnt<strlen(&st[0])){
                bool tmp=state;
                if(st[cnt]!=' ' && st[cnt]!='\n' && 
                    ( isDigit(st[cnt])|| (
                                            (isDigit(st[cnt-1])&&st[cnt]=='.') || (isDigit(st[cnt+1])&&st[cnt]=='.') 
                                         ) ||
                                         (
                                             (isDigit(st[cnt])&&st[cnt+1]=='/') || (st[cnt]=='/'&&isDigit(st[cnt+1]))
                                         ) ||
                                         (
                                             (st[cnt]=='.'&&st[cnt+1]=='/') || (st[cnt]=='/'&&st[cnt+1]=='.' || (st[cnt]=='/'&&st[cnt+1]=='-'))
                                         ) ||
                                         (
                                            (st[cnt]=='-'&&isDigit(st[cnt+1])) ||(st[cnt]=='-'&&st[cnt+1]=='.')||( st[cnt-1]=='-'&&st[cnt]=='.')
                                         )
                    ) 
                ){
                    cnt++;
                    state=true;
                    if(state!=tmp){
                        index++;
                    }
                    continue;
                }
                else if(st[cnt]!=' ' && st[cnt]!='\n' && !isDigit(st[cnt])){
                    if(once==1){
                        printf("-Dong %d chua ky tu khong phai so:",line);
                        once=2;
                    }
                    printf("%c",st[cnt]); 
                    if(st[cnt+1]==' ') printf(" ");
                    state=true; 
                    if(state!=tmp){
                        index++;
                    }
                    error=false;
                }
                else{ state=false; }
                cnt++;
            }
            if(once==2){
                printf("\b\n");li++;
                once=1;
            }
            if(index<total){printf("-Dong %d thieu %d phan tu.\n",line,total-index);li++;error=false;}                                         
            else if (index>total){ printf("-Dong %d thua %d phan tu.\n",line,index-total);li++;error=false;}
            line++;
        }
        rewind(file);
        if(!error) return false;
        return true;
}
double charToDouble(char c[]){
    double tu,sum,mau;
    int dott=0,slashh=0;
    tu=0;sum=0;mau=1;
    bool thapphan=false,phanso=false;
    for(int cnt=0;cnt<strlen(c);cnt++){
        if( isDigit(c[cnt])){
            double t=c[cnt]-'0';
            if(thapphan&&!phanso) sum += t / pow(10, cnt - dott);
            else if(!thapphan&&phanso) sum = sum * 10 + t;
            else if(thapphan&&phanso) sum +=t / pow(10, cnt - dott);
            else sum = sum * 10 + t;
            continue;
        }
        else if(c[cnt]=='.'){
            dott=cnt;
            thapphan=true;
        }
        else if(c[cnt]=='/'){
            slashh=cnt;
            tu=sum;
            sum=0;
            phanso=true;
            thapphan=false;
        }
    }
    if(phanso) mau=sum;
    else tu=sum;
    if(mau==0) throw "Phan so co mau la 0!";
    if(c[0]=='-') tu=-tu;
    if(c[slashh+1]=='-') mau=-mau;
    return tu/mau;
}
void readMatrix(FILE *file,Matrix &A){
    A.n=0;
    int max=100;
    char st[max];
    while(feof(file)==0){
        while(fgets(st,max,file)){
            A.n++;
        }
    }
    rewind(file);
    while(feof(file)==0){
        for(int i=0;i<A.n;i++){
            for(int j=0;j<A.n;j++){
                string c;
                fscanf(file,"%s ",&c[0]);
                try{
                    A.data[i][j]=charToDouble(&c[0]);
                }catch(const char* msg){
                    printf("Loi o dong %d, phan tu A[%d][%d]: ",i+1,i,j);
                    throw msg;
                }
            }
        }
    }
}
void printMatrix(Matrix A){
    printf("Kich thuoc ma tran: %d\n",A.n);
    for(int i=0;i<A.n;i++)
        printf("________");
    printf("_\n");
    for(int i=0;i<A.n;i++){
        for(int j=0;j<A.n;j++){
            printf("|%6.2f ",A.data[i][j]);
        }
        printf("|\n");
        for(int j=0;j<A.n;j++)
            printf("|_______");
        printf("|\n");
    
    }
}
bool doiXungChinh(Matrix A){
    for(int i=0;i<A.n;i++){
        for(int j=i+1;j<A.n;j++)
            if(A.data[i][j]!=A.data[j][i]) return false;        
    }
    return true;
}
bool doiXungPhu(Matrix A){
    for(int i=0;i<A.n;i++){
        for(int j=0;j<A.n-i;j++)
            if(A.data[i][j]!=A.data[A.n-1-j][A.n-1-i]) return false;        
    }
    return true;
}
double tongPhu(Matrix A){
    double sum=0; 
    for(int i=0;i<A.n;i++){
        sum+=A.data[i][A.n-1-i];
    }
    return sum;
}
template<typename T>
void iswap(T &x,T &y){
    T tmp=x;
    x=y;
    y=tmp;    
}
Matrix chuyenVi(Matrix A){
    for(int i=0;i<A.n;i++){
        for(int j=i+1;j<A.n;j++){
            iswap(A.data[i][j],A.data[j][i]);
        } 
    }
    return A;
}
void maxMoiCot(Matrix A,double x[]){
    for(int i=0;i<A.n;i++){
        double Max=-1000;
        x[i]=0;
        for(int j=0;j<A.n;j++){
            if(Max<A.data[j][i]){
                Max=A.data[j][i];
            }
            x[i]=Max;
        }
    }
}
Matrix con(Matrix A,int row,int col){
    for(int i=row;i<A.n-1;i++)
        for(int j=0;j<A.n;j++){
            A.data[i][j]=A.data[i+1][j];
        }
    for(int j=col;j<A.n-1;j++)
        for(int i=0;i<A.n;i++){
            A.data[i][j]=A.data[i][j+1];
        }
    A.n--;
    return A;
}
double dinhThucMaTran(Matrix A){
    double sum=0;
    if(A.n==1) return A.data[0][0];
    int i=0;
    int cnt;
    for(int j=0;j<A.n;j++){
        if((i+j)%2==0) cnt=1;
        else cnt=-1;
        sum+=cnt*A.data[i][j]*dinhThucMaTran(con(A,i,j));
    }
    return sum;
}
Matrix maTranTamGiac(Matrix A){
    for (int j=0; j<A.n-1; j++){
        if(A.data[j][j]==0){
            bool cotTrong=true;
            for(int i=j;i<A.n;i++){
                if(A.data[i][j]!=0){
                    for(int k=j;k<A.n;k++){
                        iswap(A.data[j][k],A.data[i][k]);
                        A.data[i][k]*=-1;
                    }
                    cotTrong=false;
                    break;
                }
            }
            if(cotTrong)
                break;
        }
        for (int i=j+1; i<A.n; i++){
            for (int k=j+1; k<A.n; k++){
                A.data[i][k] -= A.data[i][j]/A.data[j][j]*A.data[j][k];
            }
            A.data[i][j] = 0;
        }
    }
    return A;
}
double dinhThucMaTran2(Matrix TG){
    if(TG.n==1) return TG.data[0][0];
    double dinhThuc=1;
    for(int i=0;i<TG.n;i++){
            dinhThuc*=TG.data[i][i];
    }
    return dinhThuc;
}
bool nhapSoNguyen(string c,int &cv){
    getline(cin,c);
    int len=strlen(&c[0]);
    if(len>1){
        int t,sum=0;
        for(int i=0;i<len;i++){
            if(c[i]>='0'&&c[i]<='9'){
                t=c[i]-'0';
                sum=10*sum+t;
            }else if(c[i]=='-') continue;
            else{
                printf("Vui long nhap so!");
                getch();
                printf("\r");
                printf("\x1b[2K");
                return false;
            }
        }
        cv=c[0]=='-'?-sum:sum;
        if(cv<=0) {
            printf("Vui long nhap so duong");
            getch();
            printf("\r");
            printf("\x1b[2K");
            return false;
            }
    }else if(c[0]<'0'||c[0]>'9'){
        printf("Vui long nhap so!");
        getch();
        printf("\r");
        printf("\x1b[2K");
        return false;
    }else
        cv=c[0]-'0';
    return true;
}
void cau1(Matrix &A){
    A.n=0;
    string w="1. Nhap, xuat ma tran( Nhap truc tiep, nhap tu file).\n";
    printf("%s",&w[0]);
    FILE *file,*o;
    int cv,line;
    string f, c, op;
    printf("-->1. Nhap truc tiep\n");
    printf("-->2. Nhap tu file\n");
    cachnhap:
    printf("Chon cach nhap ma tran:");
    if(!nhapSoNguyen(c,cv)){ 
        printf("\x1b[1F");
        printf("\x1b[2K");           
        goto cachnhap;
    }else if(cv<1||cv>2){
        printf("Vui long chon 1 trong 2 cach");
        getch();
        printf("\r");
        printf("\x1b[2K");           
        printf("\x1b[1F");
        printf("\x1b[2K");           
        goto cachnhap;
    }
    switch  (cv){  
        case 1:
            matranA:
            printf("Nhap kich thuoc ma tran:");
            if(nhapSoNguyen(c,A.n)){
                printf("Nhap cac phan tu cho ma tran:\n");
                for(int i=0;i<A.n;i++){
                    for(int j=0;j<A.n;j++){
                        printf("A[%d][%d]=",i,j);
                        nhap:
                        string inp;
                        getline(cin,inp);
                        int len=strlen(&inp[0]);
                        if(len>=1&&inp[0]!='\n'){
                            try{
                            A.data[i][j]=charToDouble(&inp[0]);
                            }catch(const char* msg){
                                printf("%s Vui long nhap lai!",msg);
                                getch();
                                printf("\r\x1b[2K");     
                                printf("\x1b[1F");for(int k=0;k<j;k++) printf("\t\t");
                                printf("A[%d][%d]=      \b\b\b\b\b\b",i,j);
                                goto nhap;
                            }
                            fflush(stdin);
                            printf("\x1b[1F");for(int k=0;k<=j;k++) printf("\t\t");
                        }
                        else{
                            printf("\x1b[1F");for(int k=0;k<j;k++) printf("\t\t");
                            printf("A[%d][%d]=",i,j);
                            goto nhap;
                        }
                    }
                    printf("\n");
                }
            }
            else{
                printf("\r"); 
                printf("\x1b[2K");          
                printf("\x1b[1F"); 
                printf("\x1b[2K");          
                goto matranA;
            }
            w.append("-->1. Nhap truc tiep\n");
            break;   
        case 2:
            matranB:
            do{
                inputFile(&f[0]);  
                   
            }while(!checkFile(&f[0]));         
            file=fopen(&f[0],"r");
            if(!checkMatrix(file,line)){
                printf("Vui long chinh sua lai file %s hoac nhap file khac!\n",&f[0]);
                getch();
                for(int k=0;k<=line+1;k++){
                    printf("\x1b[1F"); 
                    printf("\x1b[2K");           
                }
                fclose(file);
                goto matranB;
            }
            else {
                try{
                    readMatrix(file,A);
                }catch(const char *msg){
                    printf("%s\nVui long sua lai file %s hoac nhap file khac!",msg,&f[0]);
                    getch();
                    printf("\r\x1b[2K");
                    printf("\x1b[1F");
                    printf("\x1b[2K");
                    printf("\x1b[1F");
                    printf("\x1b[2K");
                    fclose(file);
                    goto matranB;
                }
                printf("File %s chua ma tran hop le\n",&f[0]);
                sprintf(&op[0],"-->2. Nhap tu file: %s\n",&f[0]);
                w.append(&op[0]);
                fclose(file);
            }
    }
    printMatrix(A);
    saveMatrixToFile(A,w);
}
void cau2(Matrix A){
    string w="2. Kiem tra ma tran doi xung qua duong cheo chinh, duong cheo phu.\n";
    printf("%s",&w[0]);
    string op1,op2;
    int len;
    if(doiXungChinh(A)){
        op1="Ma tran doi xung qua duong cheo chinh.\n";
    }else {
        op1="Ma tran khong doi xung qua duong cheo chinh.\n";
    }
    printf("%s",&op1[0]);
    if(doiXungPhu(A)){
        op2="Ma tran doi xung qua duong cheo phu.\n";
    }else{
        op2="Ma tran khong doi xung qua duong cheo phu.\n";
    }
    printf("%s",&op2[0]);
    saveFile(w,op1.append(op2));
    saveFile("\n","");
}
void cau3(Matrix A){
    string w="3. Tinh tong gia tri cac phan tu tren duong cheo phu.\n";
    printf("%s",&w[0]);
    char op[100];
    sprintf(op, "Tong gia tri cac phan tu tren duong cheo phu=%g\n", tongPhu(A));
    printf("%s",op);
    saveFile(w,op);
    saveFile("\n","");
}
void cau4(Matrix A){
    string w="4. Tim ma tran chuyen vi.\n";
    printf("%s",&w[0]);
    printf("Ma tran chuyen vi:\n");
    printMatrix(chuyenVi(A));
    save2MatrixToFile(A,chuyenVi(A),w);
}
void cau5(Matrix A){
    string w="5. Xoa dong va cot chua phan tu nho nhat.\n";
    printf("%s",&w[0]);
    Matrix origin=A;
    char op[100];
    if(A.n>0){
        double min=1000;
        int col,row;
        for(int i=0;i<A.n;i++){
            for(int j=0;j<A.n;j++){
                if(min>A.data[i][j]){ 
                    min=A.data[i][j];
                    row=i;col=j;
                }
            }
        }
        sprintf(op, "Gia tri nho nhat tren ma tran: A[%d][%d]=%.2f\nMa tran sau khi xoa:\n",row,col,min);
        w.append(op);
        printf("%s",op);
        //don hang
        for(int i=row;i<A.n;i++)
            for(int j=0;j<A.n;j++){
                A.data[i][j]=A.data[i+1][j];
            }
        //don cot
        for(int j=col;j<A.n;j++)
            for(int i=0;i<A.n;i++){
                A.data[i][j]=A.data[i][j+1];
            }
        A.n=A.n-1;
        printMatrix(A);
        save2MatrixToFile(origin,A,w);
    }else {
        sprintf(op,"Ma tran khong co phan tu nao.\n");
        printf("%s",op);
        saveFile(w,op);
        saveFile("\n","");
    
    }
}
void cau6(Matrix A){
    string w="6. Chuyen cac phan tu lon nhat cua tung dong len duong cheo chinh.\n";
    printf("%s",&w[0]);
    Matrix origin=A;
    int col;
    for(int i=0;i<A.n;i++){
        double Max=-1000;
        for(int j=0;j<A.n;j++){
            if(Max<A.data[i][j]){
                Max=A.data[i][j];
                col=j;
            }
            
        }
        iswap(A.data[i][col],A.data[i][i]);
    }
    printMatrix(A);
    save2MatrixToFile(origin,A,w);
}
void cau7(Matrix A){
    string w="7. Tim mang 1 chieu x[n], ma x[i]=max(i)( max(i) la phan tu lon nhat trong cot i cua ma tran).\n";
    printf("%s",&w[0]);
    char ans[50];
    double x[A.n];
    maxMoiCot(A,x);
    sprintf(ans,"Mang x co: %d phan tu\n",A.n);
    printf("%s\n",ans);
    saveFile(w,ans);

    for(int i=0;i<A.n;i++){
        printf("x[%d]=%.2f  ",i,x[i]);
        sprintf(ans,"x[%d]=%.2f\t",i,x[i]);
        saveFile("",ans);
    }
    printf("\n");
    saveFile("\n\n","");
}
void cau8(Matrix A){
    string w="8. Tim dinh thuc ma tran.\n";
    printf("%s",&w[0]);
    int cv;
    string c;
    char op[100];
    printf("-->1. Cong thuc Laplace.\n");
    printf("-->2. Cong thuc Gauss.\n");
    cachnhap:
    printf("Chon cach tinh dinh thuc:");
    if(!nhapSoNguyen(c,cv)){ 
        printf("\x1b[1F");
        printf("\x1b[2K");           
        goto cachnhap;
    }else if(cv<1||cv>2){
        printf("Vui long chon 1 trong 2 cach. ");
        getch();
        printf("\r");
        printf("\x1b[2K");           
        printf("\x1b[1F");
        printf("\x1b[2K");           
        goto cachnhap;
    }
    switch  (cv){ 
        case 1:
            sprintf(op,"-->1. Cong thuc Laplace.\nDinh thuc cua ma tran det(A)=%g\n",dinhThucMaTran(A));
            printf("%s",op);
            break;
        case 2:
            sprintf(op,"-->2. Cong thuc Gauss.\nDinh thuc cua ma tran det(A)=%g\n",dinhThucMaTran2(maTranTamGiac(A)));
            printf("%s",op);
            break;
    }
    saveFile(w,op);
    saveFile("\n","");
}
int main(){
    Matrix A,B;
    string c;
    int cv;
    bool dk1=false;
    loop:
    do{ 
        system("cls");
        printf("\n                               DO AN GIAI THUAT XU LY TREN MA TRAN                               ");
        printf("\n                                             ******                                              ");
        printf("\n~                                             MENU                                              ~");
        printf("\n_________________________________________________________________________________________________");
        printf("\n|1. Nhap, xuat ma tran( Nhap truc tiep, nhap tu file).                                          |");
        printf("\n|2. Kiem tra ma tran doi xung qua duong cheo chinh, duong cheo phu.                             |");
        printf("\n|3. Tinh tong gia tri cac phan tu tren duong cheo phu.                                          |");
        printf("\n|4. Tim ma tran chuyen vi.                                                                      |");
        printf("\n|5. Xoa dong va cot chua phan tu nho nhat.                                                      |");
        printf("\n|6. Chuyen cac phan tu lon nhat cua tung dong len duong cheo chinh.                             |");
        printf("\n|7. Tim mang 1 chieu x[n], ma x[i]=max(i)( max(i) la phan tu lon nhat trong cot i cua ma tran). |");
        printf("\n|8. Tim dinh thuc ma tran.                                                                      |");
        printf("\n|9. In ma tran.                                                                                 |");
        printf("\n|0. Ket thuc chuong trinh.                                                                      |");
        printf("\n|_______________________________________________________________________________________________|");
        printf("\n+Nhap STT cong viec can thuc hien: ");
        if(!nhapSoNguyen(c,cv)) goto loop;
        switch  (cv){
            case  1:
                cau1(A);
                if(A.n>=1){dk1=true;}
                else dk1=false;
                printf("Nhan nut bat ki de tiep tuc:");break;
            case  2:
                if(dk1){
                    cau2(A);
                }else{
                    printf("Chua nhap ma tran.\n");
                }        
                printf("Nhan nut bat ki de tiep tuc:");break;
            case  3:
                if(dk1){
                    cau3(A);                  
                }else{
                    printf("Chua nhap ma tran.\n");
                }printf("Nhan nut bat ki de tiep tuc:");break;
            case  4:
                if(dk1){
                    cau4(A);                  
                }else{
                    printf("Chua nhap ma tran.\n");
                }printf("Nhan nut bat ki de tiep tuc:");break;
            case  5:
                if(dk1)
                    if(A.n<2)
                        printf("Khong the xoa luon ma tran.");
                    else              
                        cau5(A);     
                else{
                    printf("Chua nhap ma tran.\n");
                }
                printf("Nhan nut bat ki de tiep tuc:");break;
            case  6:
                if(dk1){
                    cau6(A);                  
                }else{
                    printf("Chua nhap ma tran.\n");
                }printf("Nhan nut bat ki de tiep tuc:");break;
            case  7:
                if(dk1){
                    cau7(A);                  
                }else{
                    printf("Chua nhap ma tran.\n");
                }printf("Nhan nut bat ki de tiep tuc:");break;
            case  8:
                if(dk1){
                    cau8(A);                  
                }else{
                    printf("Chua nhap ma tran.\n");
                }printf("Nhan nut bat ki de tiep tuc:");break;
            case  9:
                if(dk1){
                    printMatrix(A);
                }else{
                    printf("Chua nhap ma tran.\n");
                }printf("Nhan nut bat ki de tiep tuc:");break;
            case 0:
                system("cls");
                printf("Ket thuc chuong trinh.");
                return 0;
            default:
                printf("So qua lon, vui long nhap lai");
            };
        getch();
    }
    while  (cv!=0);
    return 0;
}