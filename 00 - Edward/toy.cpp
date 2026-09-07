//Please, ignore some comments that I made while programming, I have no experience with Bare Metal and joked 'bout it a little
//QUE LINGUAGEM PRIMITIVA É ESSA? C-------------------------------------------------------------------
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef int int32_t;
typedef long long uint64_t;
class passo{
    public:
    volatile unsigned short* vga;
    int cursor;
    int posY;
    void putchar(char c, char cor = 0x0A) {
        if (c=='\n') {
            cursor = 0;
            posY++;
            if (posY>=25) {
                posY = 0;
            }
            return;
        }
        vga[cursor+(posY*80)] =
            ((unsigned short)cor << 8) |
            (unsigned char)c;
        cursor++;
    }
};
passo mk;
#define cmd_password "Password"
#define cmd_defpassword "defPassword"
#define cmd_help "Help"
#define cmd_shhash "hashPassword"
#define cmd_clear "Clear"
#define cmd_read "Read"
#define cmd_write "writeAt"
#define cmd_list "ls"
auto hash = [](const char* str){
        unsigned int hash = 5381;
        int i = 0;
        while (str[i] != '\0') {
            hash = ((hash << 5) + hash) + str[i];
            i++;
        }
        return hash;
};
extern "C" bool strcmp(const char *s1, const char *s2){
    while (*s1 && (*s1==*s2)) {
        s1++;
        s2++;
    }
    if (*s1-*s2 == 0) {
        return true;
    }
    return false;
}
class zlib{
    private:
    public:
    class ent {
        private:
        constexpr static char ascii[128] = {
            0,  0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0,   // 0x00 - 0x0E
            0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0,   0,   // 0x0F - 0x1D
          'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',     // 0x1E - 0x2B
          'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0        // 0x2C - 0x3A
        };
        constexpr static char Ascii[128] = {
        0,  0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 0,   
        0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 0,   0,   
      'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0, '|',     
      'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' ', 0        
        };
        bool masc = false;
        static inline unsigned char batata(unsigned short porta){
            unsigned char resultado;
            __asm__ volatile("inb %1, %0" : "=a"(resultado) : "Nd"(porta));
            return resultado;
        }
        /*
        Quem me vê programar assim
        não sabe o que é sofrer
        ter que escrever assim
        sempre tão complicado
        contemplar o pesadelo do compilar
        perder a sanidade no ar
        */
        public:
        ent& operator>>(char* buffer){
            int index = 0;
            for (int i = 0; i<128; i++) {
                buffer[i] = '\0';
            }
            while (index<127) {
                if ((batata(0x64) & 0x01)!=0) {
                    unsigned char scan = batata(0x60);
                    if (scan == 0x2A || scan == 0x36) {
                        masc = true;
                        continue;
                    }
                    else if (scan == 0xAA || scan == 0xB6) {
                        masc = false;
                        continue;
                    }
                    if (scan >= 0x80) {
                        continue; 
                    }
                    if (scan<0x80) {
                        if (scan==0x1C) {
                            break;
                        }
                        else if (scan==0x0E) {
                            if (index>0) {
                                index--;
                                buffer[index] = '\0';
                                if (mk.cursor > 0) {
                                    mk.cursor--;
                                }
                                else if (mk.posY > 0) {
                                    mk.posY--;
                                    mk.cursor = 79;
                                }
                            }
                            continue;
                        }
                        char lerouB = masc?Ascii[scan]:ascii[scan];
                        if (lerouB != 0) {
                            buffer[index] = lerouB;
                            index++;
                        }
                    }
                    for(volatile int i = 0; i < 50000; i++);
                }
            }
            buffer[index] = '\0';
            return *this;
        }
    };
    class ter{
        private:
        constexpr static char ascii[128] = {
            0,  0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0,   // 0x00 - 0x0E
            0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0,   0,   // 0x0F - 0x1D
          'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',     // 0x1E - 0x2B
          'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0        // 0x2C - 0x3A
        };
        constexpr static char Ascii[128] = {
        0,  0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 0,   
        0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 0,   0,   
      'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0, '|',     
      'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' ', 0        
        };
        bool masc = false;
        static inline unsigned char batata(unsigned short porta){
            unsigned char resultado;
            __asm__ volatile("inb %1, %0" : "=a"(resultado) : "Nd"(porta));
            return resultado;
        }
        /*
        Quem me vê programar assim
        não sabe o que é sofrer
        ter que escrever assim
        sempre tão complicado
        contemplar o pesadelo do compilar
        perder a sanidade no ar
        */
        public:
        ter& operator>>(char* buffer){
            int index = 0;
            for (int i = 0; i<128; i++) {
                buffer[i] = '\0';
            }
            while (index<127) {
                if ((batata(0x64) & 0x01)!=0) {
                    unsigned char scan = batata(0x60);
                    __asm__ volatile("outb %%al, $0x80" : : "a"(0));
                    if (scan == 0x2A || scan == 0x36) {
                        masc = true;
                        continue;
                    }
                    else if (scan == 0xAA || scan == 0xB6) {
                        masc = false;
                        continue;
                    }
                    if (scan >= 0x80) {
                        continue; 
                    }
                    if (scan<0x80) {
                        if (scan==0x1C) {
                            mk.putchar('\n');
                            break;
                        }
                        else if (scan==0x0E) {
                            if (index>0) {
                                index--;
                                buffer[index] = '\0';
                                if (mk.cursor > 0) {
                                    mk.cursor--;
                                }
                                else if (mk.posY > 0) {
                                    mk.posY--;
                                    mk.cursor = 79;
                                }
                                int posicao_vga = (mk.posY * 80) + mk.cursor;
                                mk.vga[posicao_vga] = (0x0A << 8) | ' ';
                            }
                            continue;
                        }
                        char lerouB = masc?Ascii[scan]:ascii[scan];
                        if (lerouB != 0) {
                            buffer[index] = lerouB;
                            index++;
                            mk.putchar(lerouB);
                        }
                    }
                }
            }
            buffer[index] = '\0';
            return *this;
        }
    };
    class out {
        private:
        char cor = 0x0A;
        public:
        out& operator<<(const char* buffer){
            for (int i = 0; buffer[i] != '\0'; ++i) {
                mk.putchar(buffer[i], cor);
            }
            return *this;
        }
        out& operator<<(uint64_t num){
            if (num == 0) {
                mk.putchar('0', cor);
                return *this;
            }
            if (num < 0) {
                mk.putchar('-', cor);
                num = -num;
            }
            char buffer[12];
            int i = 0;
            while (num>0) {
                buffer[i] = (num % 10) + '0';
                num /= 10;
                i++;
            }
            for (int j = i-1; j>=0; j--) {
                mk.putchar(buffer[j], cor);
            }
            return *this;
        };
    };
};
zlib::ent zin;
zlib::out zout;
zlib::ter zint;
class iot{
    public:
    class io{
        public:
        template<typename T>
        io& operator>=(T* buffer){
            zin>>buffer;
            return *this;
        }
        template<typename T>
        io& operator<<(const T* buffer){
            zout<<buffer;
            return *this;
        }
        template<typename T>
        io& operator>>(T* buffer){
            zint>>buffer;
            return *this;
        }
    };
};
iot::io zio;


class PassWord{
    public:
    unsigned int passwort = 0;
    int defPasswort(const char* passwort2){
        passwort = hash(passwort2);
        return 0;
    }
}; inline PassWord p;
bool conf(const char* senha){
    bool acesso;
    if (hash(senha)==p.passwort) {
        acesso = true;
        zout<<"Right Password";
    } else {
        acesso = false;
        zout<<"Wrong Password";
    }
    return acesso;
}
struct arqv{
        char nome[128];
        char cont[2048];
        bool sec;
    }; arqv files[128];
void leitorDeComandos(const char *entrada){
    
    constexpr unsigned int IDSENHA = hash(cmd_password);
    constexpr unsigned int IDDEFSENHA = hash(cmd_defpassword);
    constexpr unsigned int IDHELP = hash(cmd_help);
    constexpr unsigned int IDSHHASH = hash(cmd_shhash);
    constexpr unsigned int IDCLEAR = hash(cmd_clear); 
    constexpr unsigned int IDWRITE = hash(cmd_write);
    constexpr unsigned int IDREAD = hash(cmd_read);
    constexpr unsigned int IDLIST = hash(cmd_list);

    auto iftrue = [](){
        zout<<"Password: ";
        char sen[128];
        zin>>sen; 
        p.defPasswort(sen);
        zout<<"Password defined";
    };
    auto iffalse = [](){
        zout<<"Actual password: ";
        char senhaAntiga[128];
        zin >> senhaAntiga;
        if (conf(senhaAntiga)){
            zout<<"\nRight password\nnew password: ";
            char novaSenha[128];
            zin>>novaSenha;
            p.defPasswort(novaSenha);
        }
    };
    constexpr auto list = [](){
        zout<<"Help\ndefPassword\nPassword\nhashPassword\nClear\nRead\nwriteAt\nls";
    };
    auto sn = [](){
        zout<<"senha: ";
        char pass[128];
        zin>>pass;
        bool corr = conf(pass);
        return corr;
    };
    auto ext = [&](char inpu[128]){
        for(int i = 0; i<64; i++){
            if(strcmp(inpu, files[i].nome)){
                return i;
            }
        }
        return -1;
    };
    int indexC = 0;
    static short fnum = 0;
    int pos;
    arqv temp;
    switch (hash(entrada)) {
        case IDLIST:
            for (int i = 0; i<fnum; i++) {
                zout<<files[i].nome;
            }
            break;
        case IDWRITE:
            zio<<"nome: ">>temp.nome;
            pos = ext(temp.nome);
            if(pos<0){
                char tr[5];
                int index = 0;
                while (temp.nome[index] != '\0') {
                    files[fnum].nome[index] = temp.nome[index];
                    ++index;
                }
                zio<<"Should be protected?[true or false]\n">>tr<<"content:\n">>files[fnum].cont;
                if (strcmp(tr, "true")) {
                    files[fnum].sec = true;
                }
                else {
                    files[fnum].sec = false;
                }
                fnum++;
            }
            else {
                if(files[pos].sec){
                    while (true) {
                        temp.sec = sn();
                        if(temp.sec){
                            break;
                        }
                    }
                    zio<<"content: ">>files[pos].cont;
                }
                else {
                    zio<<"content: ">>files[pos].cont;
                }
            }
            break;
        case IDREAD:
            if(true){
                char nome[128];
                zio<<"nome: ">>nome;
                bool enc = false;
                for (short i = 0; i < fnum; i++) {
                    if(strcmp(nome, files[i].nome)){
                        if (files[i].sec == true) {
                            while (!sn());
                            zio<<"\n";
                        }
                        zout<<files[i].cont;
                        enc = true;
                        break;
                    }
                }
                if(!enc){
                    zout<<"Unknown";
                }
            }
            break;
        case IDSENHA:
            sn();
            break;
        case IDDEFSENHA:
            p.passwort == 0? iftrue() : iffalse();
            break;
        case IDHELP:
            list();
            break;
        case IDSHHASH:
            zout<<p.passwort;
            break;
        case IDCLEAR:
            mk.cursor = 0;
            mk.posY = 0;
            while (indexC < 2000) {
                mk.putchar(' ');
                indexC++;
            }
            mk.posY = 0;
            mk.cursor = 0;
            break;
        default:
            zout<<"Type help for the command list";
            break;
    }
}
extern "C" void toy(){
    mk.vga = (volatile unsigned short*)0xB8000;
    mk.cursor = 0;
    zout<<"IT'S ALIVE, IT'S ALIVE! \nEdward>";
    bool terminal = true;
    while (terminal) {
        char input[128];
        zint>>input;
        leitorDeComandos(input);
        zout<<"\nEdward>";
    }
}
