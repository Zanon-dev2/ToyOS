typedef unsigned long long size_t;
constexpr char blackout = 0x00;

constexpr char verdeEB = 0x20;
constexpr char vermelhoEB = 0x40;
constexpr char cinzaCB = 0x70;
constexpr char cinzaEB = 0x80;
constexpr char azulB = 0x90;
constexpr char verdeCB = 0xA0;
constexpr char cianoCB = 0xB0;
constexpr char amareloB = 0xE0;
constexpr char brancoB = 0xF0;

constexpr char vermelhoEL = 0x04;
constexpr char verdeCL = 0x0A;
constexpr char cianoCL = 0x0B;
constexpr char amareloL = 0x0E;
constexpr char brancoL = 0x0F;


extern "C" void* memcpy(void* dest, const void* src, size_t n){
    char* d = reinterpret_cast<char*>(dest);
    const char* s = reinterpret_cast<const char*>(src);
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}
namespace var {
    struct ztring{
        char mem[4096] = {'\0'};
        int size = 0;

        ztring() : size(0) {
            mem[0] = '\0';
        }

        char& operator[](int i){return mem[i];}
        char* begin(){
            return &mem[0];
        }
        char* end(){return &mem[size];}
        const char* begin() const{return &mem[0];}
        const char* end() const{return &mem[size];}
        const char& operator[](int i) const {return mem[i];}

        ztring(const char* texto){
            size = 0;
            if (texto != nullptr) {
                while (texto[size] != '\0' && size < 4095) {
                    mem[size] = texto[size];
                    size++;
                }
            }
            mem[size] = '\0';
        }
        ztring(int num){
            size = 0;
            if (num == 0){
                mem[0] = '0';
                mem[1] = '\0';
                size = 1;
                return;
            }
            bool n = false;
            if (num < 0) {
                n = true;
                num = -num;
            }
            char tmp[24];
            int tdx = 0;
            while (num > 0) {
                tmp[tdx++] = num % 10 + '0';
                num /= 10;
            }
            if (n && size < 4095) {
                mem[size++] = '-';
            }
            for (int j = tdx-1; j>=0 && size<4095; j--) {
                mem[size++] = tmp[j];
            }
            mem[size] = '\0';
        }
        int length() const {
            int len = 0;
            while (mem[len] != '\0' && len < 8191) {
                len++;
            }
            return len;
        }
        ztring& operator=(const char* buffer){
            size = 0;
            if (buffer != nullptr) {
                while (buffer[size] != '\0' && size <4095) {
                    mem[size] = buffer[size];
                    size++;
                }
                mem[size] = '\0';
            }
            
            return *this;
        }
        bool operator==(const ztring& buff) const {
            int i = 0;
            while (mem[i] != '\0' && buff[i] != '\0') {
                if (mem[i] != buff[i]) {
                return false;
                }
                ++i;
            }
            if (mem[i] != buff[i]) {
                return false;
            }
            return true;
        }
        bool operator!=(const ztring& buff) const {
            return !(*this == buff);
        }
        static ztring ztr(const char* buff){
            return ztring(buff);
        }
        const unsigned int operator()(ztring wrd) const {
            int hash = 5381; int i = 0;
            while (wrd.mem[i] != '\0') {
                hash = (wrd.mem[i]<<5)+hash;
                i++;
            }
            return hash;
            }
    };
    struct app{
        var::ztring nm;
        char cor;
        bool sel = false;
    };
    /*typedef struct frac{
        long long vl;
        unsigned int fraq;
        frac& operator/(long long buff){
            long long temp = vl/buff * 10000;
            
        };
    } precise;*/
    
    enum setas{
        nn = 0,
        up,
        dw,
        esq,
        dir,
        sel,
        esc,
        w,
        s,
        shp,
        shb
    };
    int password = 0;
    ztring pas;
    unsigned int delay = 999000;
    int lp = 0;
    int acp = 0;
    int bp = 0;
}
var::app arqop[32];
var::ztring NULL = "\0";
namespace txt {
    class print{
        private:
        
        public:
        volatile unsigned short* vga;
        int X, Y;
        constexpr void putchar(const char c, const char cor = cianoCL){
            if (c=='\n') {
                Y++;
                X = 0;
                if (Y >= 25) {
                    Y=0;
                }
                return;
            }
            vga[X+(Y*80)] = ((unsigned short)cor << 8) | (unsigned char)c;
            X++;
        }
        
    }; print write;
    print wr;
    void writeAt(const var::ztring& frase, int x, int y, const char cor = cianoCL){
        wr.vga = (volatile unsigned short*)0xB8000;
        for(int i = 0; i < frase.size; i++){
            wr.vga[x+(y*80)] = ((unsigned short)cor<<8) | (unsigned char)frase.mem[i];
            x++;
        }
    }
    //I'll write the graf namespace right here 'cause it uses the vga to simulate images with text
    namespace graf {
        print img;
        void setpx(const char cor, int x, int y, char c = ' '){
            img.vga = (volatile unsigned short*)0xB8000;
            img.X = x;
            img.Y = y;
            img.vga[img.X+(img.Y*80)] = ((unsigned short)cor << 8) | (unsigned char)c;
        }
        void drBox(const char cor, int xi, int yi, int xl = 1, int yl = 1){
            int s = xi;
            xl = 2 * xl;
            for (int i = 0; i<yl; i++) {
                for (int j = 0; j < xl; j++) {
                    setpx(cor, xi, yi);
                    xi++;
                } 
                yi++;
                xi = s;
            } 
        }
        void wall(const char cor){
            drBox(cor, 0, 0, 80, 25);
        }
        void ico(const var::ztring& nome, bool slc, int x, int y, const char cor, const char ncor, int sz = 5, char bcor = verdeCB){
            int bx = (x > 0) ? x - 1 : 0;
            int by = (y > 0) ? y - 1 : 0;
            if (slc) {
                drBox(blackout, bx, by, sz+1, sz+2);
            }
            else {
                drBox(bcor, bx, by, sz+1, sz+2);
            }
            drBox(cor, x, y, sz, sz);
            int cent = sz/2;
            int reY, reX, pos;
            if ((sz%2) != 0) {
                cent++;
            }
            reY = (y+cent);
            pos = (sz*2) - nome.size;
            reX = x + (pos/2);
            if (reX < x) {reX = x;}
            for (int i = 0; i < nome.size; i++) {
                if ((reX+i) >= 80) {break;}
                setpx(ncor, reX+i, reY, nome.mem[i]);
            }
        }
        void applist(var::app pp[32], int X, int Y){
            short par = 0;
            int sx = X;
            for (int i = 0; i < 32; i++) {
                if(pp[i].nm != NULL){
                    par++;
                }
            }
            short pr = 0;
            for(int i = 0;i < par; i++){
                ico(pp[i].nm, pp[i].sel, X, Y, pp[i].cor, amareloB, 5, cianoCB);
                X += 16;
                pr++;
                if (pr >= par / 2) {
                    Y += 8;
                    X = sx;
                    pr = 0;
                }
            }
        }
    }
    class out{
        private:
        char cor = cianoCL;
        bool prec = false;
        public:
        void espCase(const bool def){
            prec = def;
        }
        void setCor(const char ncor){
            cor = ncor;
        }
        out& operator<<(const var::ztring& buff){
            for (char c : buff) {
                write.putchar(c, cor);
            }
            return *this;
        }
        out& operator<<(const char* buff){
            for (long i = 0; buff[i] != '\0'; i++) {
                write.putchar(buff[i], cor);
            }
            return *this;
        }
        out& operator<<(char buff){
            write.putchar(buff, cor);
            return *this;
        }
        out& operator<<(int buff){
            if (buff == 0) {
                write.putchar('0', cor);
                return *this;
            }
            if (buff < 0) {
                write.putchar('-', cor);
                buff = -buff;
            }
            char buffer[12];
            int i = 0;
            while (buff>0) {
                buffer[i] = (buff % 10) + '0';
                buff /= 10;
                i++;
            }
            for (int j = i-1; j>=0; j--) {
                write.putchar(buffer[j], cor);
            }
            return *this;
        }
        out& operator<<(long long buff) {
            bool negativo = buff < 0;

            unsigned long long valor =
                negativo ? 0ULL - (unsigned long long)buff
                        : (unsigned long long)buff;

            char buffer[20];
            int i = 0;

            do {
                buffer[i++] = (valor % 10) + '0';
                valor /= 10;
            } while (valor > 0);

            if (negativo) {
                write.putchar('-', cor);
            }
            if (!prec) {
                for (int j = i - 1; j >= 0; --j) {
                    write.putchar(buffer[j], cor);
                }
            } else {
                while (i <= 4) {
                    buffer[i++] = '0';
                }
                for (int j = i - 1; j >= 0; --j) {
                    if (j == 3) {
                        write.putchar('.', cor);
                    }
                    write.putchar(buffer[j], cor);
                }
            }
            prec = false;
            return *this;
        }
    }; out zout;
    class in{
        protected:
        static inline unsigned char rd(unsigned short porta){
            unsigned char ent;
            __asm__ volatile (
                "inb %1, %0"
                : "=a"(ent)
                : "Nd"(porta)
            );
            return ent;
        }
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
        bool uppr = false;
        bool wrt = false;
        char cor = cianoCL;
        public:
        bool escp;
        bool espcase = false;
        void esc(bool wr){
            wrt = wr;
        }
        in& operator>>(var::ztring& buff){
            int index = 0;
            if (!espcase) {
                buff = NULL;
            }
            else {
                index = buff.size;
            }
            while (index < 16384) {
                if ((rd(0x64) & 0x01) != 0) {
                    unsigned char lt = rd(0x60);
                    if (lt == 0x2A || lt == 0x36) {
                        uppr = true;
                        continue;
                    }
                    else if (lt == 0xAA || lt == 0xB6) {
                        uppr = false;
                        continue;
                    }
                    else if(lt == 0x0F){
                        for (int i = 0; i < 5; i++) {
                            buff[index] = ' ';
                            if (wrt) { write.putchar(' ', cor); }
                            index++;
                        }
                        buff.size = index;
                        continue;
                    }
                    if(lt >= 0x80) {
                        continue; 
                    }
                    else if (lt < 0x80) {
                        if (lt == 0x1C) {
                            if (wrt) {write.putchar('\n', cor);}
                            if (espcase) {
                                buff[index] = '\n';
                                index++;
                            }
                            break;
                        }
                        else if (lt == 0x01) {
                            escp = true;
                            break;
                        }
                        else if (lt == 0x0E) {
                            if (index > 0) {
                                index--;
                                buff.mem[index] = '\0';
                                if(write.X>0){
                                    write.X--;
                                }
                                else if (write.Y>0) {
                                    write.Y--;
                                    write.X = 79;
                                }
                                int pos = (write.Y*80) + write.X;
                                if(wrt){write.vga[pos] = (cor << 8) | ' ';}
                            }
                            continue;
                        }
                        char act = uppr?Ascii[lt]:ascii[lt];
                        if (act!=0) {
                            buff[index] = act;
                            index++;
                            if (wrt) {write.putchar(act, cor);}
                        }
                    }
                    for (volatile int i = 0; i < 5000; i++);
                }
            }
            buff[index] = '\0';
            buff.size = index;
            espcase = false;
            return *this;
        }
        void setCor(const char ncor){
            cor = ncor;
        }
        in& operator>>(char& buff){
            while (true) {
                if ((rd(0x64) & 0x01) != 0) {
                unsigned char lt = rd(0x60);
            if (lt == 0x2A || lt == 0x36) {
                uppr = true;
                continue;
            }
            else if (lt == 0xAA || lt == 0xB6) {
                uppr = false;
                continue;
            }
                if(lt >= 0x80) {
                    continue;
                }
                else if (lt < 0x80) {
                    if (lt == 0x1C) {
                        if (wrt) {write.putchar('\n', cor);}
                    }
                    else if (lt == 0x01) {
                        escp = true;
                    }
                    buff = uppr?Ascii[lt]:ascii[lt];
                    if (wrt) {write.putchar(buff, cor);}
                    break;
            }
            }
            }
            return *this;
        }
        friend class workspace;
    }; in zin;
    class ever{
        public:
        void setCor(const char ncor){
            zin.setCor(ncor);
            zout.setCor(ncor);
        }
        template<typename T>
        ever& operator<<(T&& buffer){
            zout<<buffer;
            return *this;
        }
        ever& operator>>(char& buff){
            zin.esc(true);
            zin>>buff;
            return *this;
        }
        ever& operator>>(var::ztring& buffer){
            zin.esc(true);
            zin>>buffer;
            return *this;
        }
        ever& operator<=(var::ztring& buff){
            zin.esc(false);
            zin>>buff;
            return *this;
        }
        ever& operator>>(int& buff){
            zin.esc(true);
            var::ztring in;
            zin>>in;
            if (zin.escp) {
                return *this;
            }
            int ret = 0;
            for (int i = 0; in.mem[i] != '\0'; i++) {
                char c = in.mem[i];
                if (c >= '0' && c <= '9') {
                    ret = (ret*10) + (c - '0');
                }
                else {
                    zout<<"entrada errada";
                    break;
                }
            }
            buff = ret;
            return *this;
        }
        ever& operator>>(long long& buff){
            bool n = false;
            zin.esc(true);
            var::ztring in;
            zin>>in;
            if (zin.escp) {
                return *this;
            }
            long long ret = 0;
            for (int i = 0; in.mem[i] != '\0'; i++) {
                char c = in.mem[i];
                if (c >= '0' && c <= '9') {
                    ret = (ret*10) + (c - '0');
                }
                else if (in.mem[0] == '-') {
                    n = true;
                }
                else {
                    zout<<"entrada errada";
                    break;
                }
            }
            if (n) {
                ret = 0 - ret;
            }
            buff = ret;
            return *this;
        }
    }; ever zio;
    void ident(int X, int Y){
        for (int i = 0; i < (X + Y*80); i++) {
            zio<<" ";
        }
    }
    constexpr unsigned int hash(const var::ztring& wrd){
        int hash = 5381; int i = 0;
        while (wrd.mem[i] != '\0') {
            hash = (wrd.mem[i]<<5)+hash;
            i++;
        }
        return hash;
    }
    constexpr unsigned int hash(const char* wrd){
        int hash = 5381; int i = 0;
        while (wrd[i] != '\0') {
            hash = (wrd[i]<<5)+hash;
            i++;
        }
        return hash;
    }
}

class workspace : public txt::in{
    private:
    public:
    var::setas stread(){
        if((rd(0x64) & 1) == 1){
            volatile int timer = 0;
            while ((rd(0x64)&1)==0) {
                __asm__ volatile("pause");
                timer++;
                if (timer>8000) {
                    return var::nn;
                }
            }
            unsigned char pref = rd(0x60);
            if (pref == 0xE0) {
                pref = rd(0x60);
                switch (pref) {
                    case 0x48:
                        return var::up;
                    case 0x50:
                        return var::dw;
                    case 0x4B:
                        return var::esq;
                    case 0x4D:
                        return var::dir;
                    default:
                        return var::nn;
                }
            }
            else {
                switch (pref) {
                    case 0x11:
                        return var::w;
                        break;
                    case 0x1F:
                        return var::s;
                        break;
                    case 0x1C:
                        return var::sel;
                        break;
                    case 0x01:
                        return var::esc;
                        break;
                    case 0x36:
                        return var::shp;
                        break;
                    case 0xB6:
                        return var::shb;
                        break;
                    case 0x2A:
                        return var::shp;
                        break;
                    case 0xAA:
                        return var::shb;
                        break;
                    default:
                        break;
                }
            }
        }
        return var::nn;
    }
    void window(){
        txt::graf::wall(verdeCB);
        txt::writeAt("Tanya", 40, 2, vermelhoEL+verdeCB);
    }
    void apps(bool fl, bool calc, bool ter, bool jg){
        txt::graf::ico("Snake", jg, 14, 12, verdeEB, verdeCL);
        txt::graf::ico("Terminal", ter, 2, 5, cinzaCB, verdeCL);
        txt::graf::ico("Calculadora", calc, 14, 5, cinzaEB, brancoL);
        txt::graf::ico("Files", fl, 2, 12, amareloB, cianoCL);
    }
    void bar(int ch){
        bool ter = false, calc = false, fl = false, jg = false;
        switch (ch) {
            case 0:
                ter = true;
                calc = false;
                fl = false;
                jg = false;
                break;
            case 1:
                calc = true;
                ter = false;
                fl = false;
                jg = false;
                break;
            case 2:
                fl = true;
                ter = false;
                calc = false;
                jg = false;
                break;
            case 3:
                jg = true;
                ter = false;
                calc = false;
                fl = false;
                break;
            default:
                break;
        }
        apps(fl, calc, ter, jg);
        for (volatile int i = 0; i<1000; i++) {
            __asm__ volatile("pause");
        }
    }
}; workspace ws;
//a separate namespace for terminal features
namespace tmn {
    #define cui constexpr unsigned int
    cui helpID = txt::hash("Help");
    cui defpassID = txt::hash("defPassword");
    cui clearID = txt::hash("Clean");
    bool check(const var::ztring& in){
        if (txt::hash(in) == var::password) {
            return true;
        }
        return false;
    }
    void readCmd(const var::ztring& cmd){
        switch (txt::hash(cmd)) {
            case helpID:
                txt::zio<<"Press ESC to finish\nHelp\ndefPassword\nClean\n";
                break;
            case defpassID:
                if(var::password != 0){
                    while (true) {
                        txt::zio<<"[type giveUp to give up]\nOld password: \n"<=var::pas;
                        if (check(var::pas)) {
                            break;
                        }
                        else if (var::pas == "giveUp") {
                            return;
                        }
                    }
                }
                txt::zio<<"[It cant't be giveUp]\nType the new password"<=var::pas;
                var::password = txt::hash(var::pas);
                txt::zio<<"\nPassword defined\n";
                break;
            case clearID:
                txt::graf::wall(blackout);
                txt::write.X = 0;
                txt::write.Y = 0;
                break;
            default:
                txt::zio<<"Unknown, type Help\n";
                break;
        }
    }
}
//a separate namespace for files features
namespace fls {
        struct zimg{
            var::ztring name = NULL;
            unsigned char pxs[2000];
            bool prot = false;
            bool slc = false;
            void show(const zimg load){
            int pxx = 0;
            int pxy = 0;
            for (int i = 0; i<2000; i++) {
                txt::graf::setpx(load.pxs[i], pxx, pxy);
                pxx++;
                pxy++;
            }
            }
        };
        struct zxt{
            var::ztring name = NULL;
            var::ztring content;
            bool prot = false;
            bool slc = false;
        };
        zxt tls[33];
        zimg ils[33];
    void listImg(zimg arqs[33]){
        int x = 3;
        int y = 1;
        int sv = x;
        for (int i = 0; i < 33; i++) {
            if (x >= 80) {
                x = sv;
                y += 7;
            }
            if (arqs[i].name == NULL) {
                break;
            }
            txt::graf::ico(arqs[i].name, arqs[i].slc, x, y, amareloB, verdeCL, 4, cinzaCB);
            x+=13;
        }
    }
    void listTxt(zxt arqs[33]){
        int x = 3;
        int y = 1;
        int sv = x;
        for (int i = 0; i < 33; i++) {
            if (x >= 80) {
                x = sv;
                y += 7;
            }
            if (arqs[i].name == NULL) {
                break;
            }
            txt::graf::ico(arqs[i].name, arqs[i].slc, x, y, amareloB, verdeCL, 4, cinzaCB);
            x+=13;
        }
    }
    void RIT(zimg arqs[33], int sel){
        if (arqs[sel].prot && var::password != 0) {
            txt::graf::wall(verdeCB);
            bool ch = true;
            while (true) {
                txt::zio.setCor(verdeCB);
                txt::write.X = 0;
                txt::write.Y = 0;
                bool wrg = !ch;
                if (wrg) {
                    txt::zio<<"Wrong Password, try again\n";
                }
                txt::zio<<"[type giveUp to give up]\nProtected, your password: \n"<=var::pas;
                if (var::pas == "giveUp") {
                    return;
                }
                ch = tmn::check(var::pas);
                
                if (ch) {
                    break;
                }
            }
        }
        for (int i = 0; i< 33; i++) {
            if(sel == i){
                int p = 0;
                for (int y = 0;y<25; y++) {
                    for (int x = 0; x < 80; x++) {
                        txt::graf::setpx(arqs[i].pxs[p], x, y);
                        p++;
                    }
                }
            }
        }
        bool cnt = true;
        while (cnt) {
            var::setas ex = ws.stread();
            if (ex == var::esc) {
                cnt = false;
            }
        }
    }
    void RT(zxt arqs[33], int sel){
        if (arqs[sel].prot && var::password != 0) {
            txt::graf::wall(verdeCB);
            bool ch = true;
            while (true) {
                txt::zio.setCor(verdeCB);
                txt::write.X = 0;
                txt::write.Y = 0;
                bool wrg = !ch;
                if (wrg) {
                    txt::zio<<"Wrong Password, try again\n";
                }
                txt::zio<<"[type giveUp to give up]\nProtected, your password: \n"<=var::pas;
                if (var::pas == "giveUp") {
                    return;
                }
                ch = tmn::check(var::pas);
                
                if (ch) {
                    break;
                }
            }
        }
        bool found = false;
        for (int i = 0; i<33; i++) {
            if (sel == i && arqs[i].name != NULL) {
                found = true;
                break;
            }
        }
        if(!found){
            return;
        }
        else {
            txt::graf::wall(blackout);
            txt::write.X = 0;
            txt::write.Y = 0;
            txt::zout.setCor(cianoCL);
            txt::ident(5, 0);
            txt::zio<<arqs[sel].content;
            while (true) {
                var::setas esc = ws.stread();
                if (esc == var::esc) {
                    return;
                }
            }
        }
    }
}
//a separate namespace for Snake Game
namespace Snake {
    constexpr int W = 40;
    constexpr int H = 16;
    constexpr int X0 = 20;
    constexpr int Y0 = 4;
    constexpr int MAX = W * H;

    constexpr char emp = ' ';
    constexpr char head = '@';
    constexpr char bd = 'o';
    constexpr char fd = '*';

    int sx[MAX];
    int sy[MAX];

    int len = 3;
    int fx = 10;
    int fy = 8;
    
    int dx = 1;
    int dy;

    unsigned int seed = 12345 + var::password;
    bool alive = true;
    unsigned int rand(){
        int randic = (var::bp + var::acp)/(var::lp+3);
        seed = seed * 1103515245u + 12345u + (dy * 357) + randic;
        return (seed >> 16) & 0x7FFF;
    }
    void cell(int x, int y, char c, char cor){
        txt::graf::setpx(cor, X0 + x, Y0 + y, c);
    }
    void draw(){
        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {
                cell(x, y, emp, blackout);
            }
        }
        for (int x = -1; x <= W; x++){
            cell(x, -1, '#', cianoCL);
            cell(x, H, '#', cianoCL);
        }
        for (int y = 0; y < H; y++) {
            cell(-1, y, '#', cianoCL);
            cell(W, y, '#', cianoCL);
        }
        cell(fx, fy, fd, vermelhoEL);
        for(int i = len - 1; i >= 0; i--){
            cell(sx[i], sy[i], i == 0 ? head : bd, i == 0 ? amareloL : verdeCL);
        }
    }
    bool ocp(int x, int y){
        for (int i = 0; i < len; i++){
            if (sx[i] == x && sy[i] == y) {
                return true;
            }
        }
        return false;
    }
    void spFd(){
        for (int _try = 0; _try < MAX; _try++){
            fx = rand() % W;
            fy = rand() % H;
            if(!ocp(fx, fy)){
                return;
            }
        }
        alive = false;
    }
    void reset(){
        len = 3;

        dx = 1;
        dy = 0;

        alive = true;
        seed += 17;

        sx[0] = 20;
        sy[0] = 8;

        sx[1] = 19;
        sy[1] = 8;

        sx[2] = 18;
        sy[2] = 8;

        spFd();
        draw();
    }
    void turn(var::setas key) {
        if (key == var::up && dy != 1) {
            dx = 0;
            dy = -1;
        }
        else if (key == var::dw && dy != -1) {
            dx = 0;
            dy = 1;
        }
        else if (key == var::esq && dx != 1) {
            dx = -1;
            dy = 0;
        }
        else if (key == var::dir && dx != -1) {
            dx = 1;
            dy = 0;
        }
        else if (key == var::w) {
            var::delay += 9000;
        }
        else if (key == var::s) {
            var::delay -= 9000;
        }
    }
    void tick(){
        int nx = sx[0] + dx;
        int ny = sy[0] + dy;

        bool eating = (nx == fx && ny == fy);
        if (eating) {
            var::acp++;
        }
        if(nx < 0 || nx >= W || ny < 0 || ny >= H){
            alive = false;
            return;
        }
        int lm = eating ? len : len - 1;
        for (int i = 0; i < lm; i++){
            if(sx[i] == nx && sy[i] ==ny){
                alive = false;
                return;
            }
        }
        if (eating && len < MAX){
            len++;
        }
        for (int i = len - 1; i > 0; i--) {
            sx[i] = sx[i - 1];
            sy[i] = sy[i - 1];
        }

        sx[0] = nx;
        sy[0] = ny;

        if (eating) {
            spFd();
        }
        draw();
    }
    void Central(){
        var::acp = 0;
        txt::graf::wall(azulB);
        txt::write.X = 3;
        txt::write.Y = 22;
        txt::zio<<"Last Pontuation: "<<var::lp;
        txt::write.X = 3;
        txt::write.Y = 21;
        txt::zio<<"Best Pontuation: "<<var::bp;
        reset();
        unsigned int delay = 0;
        unsigned int svacp = 1;
        while (alive) {
            var::setas key = ws.stread();
            if (var::acp != svacp) {
                txt::write.X = 3;
                txt::write.Y = 23;
                txt::zio<<"Pontuation: "<<var::acp;
                svacp = var::acp;
            }
            switch (key) {
                case var::esc:
                    alive = false;
                    break;
                case var::nn:
                    break;
                default:
                    turn(key);
                    break;
            }
            delay++;
            if (delay >= var::delay) {
                delay = 0;
                tick();
            }
        }
        txt::graf::wall(blackout);
        txt::writeAt("GAME OVER - ESC", 30, 12, brancoL);
        while (true) {
            var::setas end = ws.stread();
            if (end != var::nn) {
                break;
            }
        }
        if (var::acp > var::bp) {
            var::bp = var::acp;
        }
        var::lp = var::acp;
        ws.window();
    }
}

class funcs{
    private:
    short flpos = 0;
    unsigned char cscr = 0;
    unsigned char svcscr = 0;
    var::ztring input;
    var::setas paint;
    void ter(){
        txt::graf::wall(0x00);
        txt::write.X = 0;
        txt::write.Y = 0;
        txt::zin.setCor(cianoCL);
        txt::zout.setCor(cianoCL);
        while (!txt::zin.escp) {
            txt::zio<<"Tanya>">>input;
            tmn::readCmd(input);
        }
        txt::zin.escp = false;
    }
    void calc(){
        long long c = 0;
        long long res = 0;
        static constexpr auto clean = [](){
            txt::graf::wall(cinzaEB);
            txt::graf::drBox(cinzaCB, 10, 3, 30, 6);
        };
        auto div = [&](long long a, long long b){
            txt::zout.espCase(true);
            c = (a*10000)/b;
        };
        auto prdv = [&](){
            txt::zout.espCase(true);
            txt::write.Y = 4;
            txt::write.X = 12;
            txt::zout.setCor(cianoCL+cinzaCB);
            txt::zio<<c;
        };
        clean();
        int resx = txt::write.X;
        int resy = txt::write.Y;
        bool dv = false;
        while (!txt::zin.escp) {
            txt::graf::drBox(cinzaEB, 0, 9, 80, 16);
            long long n1;
            long long n2;
            char op;
            clean();
            if(!dv){txt::writeAt(res, 12, 4, cianoCL+cinzaCB);}
            else {prdv();}
            txt::write.X = 0;
            txt::write.Y = 9;
            dv = false;
            txt::zout.setCor(cianoCL+cinzaEB);
            txt::zin.setCor(cianoCL+cinzaEB);
            txt::writeAt("It has a limit and turns numbers that overflows the memory in negatives", 0, 1, cianoCL+verdeEB);
            txt::zio<<"First num\n">>n1<<"Second num\n">>n2<<"Operation[+, -, *, /]\n">>op;
            switch (op) {
                case '-':
                    res = n1-n2;
                    break;
                case '+':
                    res = n1+n2;
                    break;
                case '*':
                    res = n1*n2;
                    break;
                case '/':
                    div(n1, n2);
                    dv = true;
                    break;
                default:
                    txt::zio<<"Unknown operator";
                    break;
            }
        }
        txt::zout.setCor(cianoCL);
        txt::zin.setCor(cianoCL);
        txt::write.X = resx;
        txt::write.Y = resy;
        txt::zin.escp = false;
    }
    void Draw(){
        txt::write.X = 5;
        txt::write.Y = 3;
        txt::graf::wall(vermelhoEB);
        var::ztring nm;
        txt::zio.setCor(amareloL + vermelhoEB);
        txt::zio<<"Name: ">>nm;
        short n = 0;
        for (short i = 0; i<=33; i++) {
            if (fls::ils[i].name == nm || fls::ils[i].name == NULL) {
                break;
            }
            n++;
        }
        if(n>=33){
            txt::zio<<"FULL";
            txt::zio<<"PRESS ANYTHING";
            ws.stread();
            return;
        }
        else {
            fls::ils[n].name = nm;
        }
        char sl;
        txt::zio<<"Protected? [y/n]">>sl;
        if (sl == 'y' || sl == 'Y') {
            fls::ils[n].prot = true;
        }
        bool cnt = true;
        txt::zio.setCor(blackout);
        txt::zio<<' ';
        txt::graf::wall(blackout);
        int py = 0, px = 0;
        unsigned char screen[2000] = {'\0'};
        unsigned char scrn[2000] = {'\0'};
        bool dr = false;
        while (cnt) {
            txt::zio.setCor(cscr);
            int x = 0, y = 0;
            for (int i = 0; i<2000; i++) {
                if (screen[i] != scrn[i]){
                    txt::graf::setpx(screen[i], x, y);
                }
                x++;
                if(x>=80){
                    y++;
                    x = 0;
                }
            }
            if (cscr != svcscr || py != txt::write.Y || px != txt::write.X) {
                txt::zin.setCor(cscr);
                txt::zio<<' ';
                txt::write.X--;
                svcscr = cscr;
                py = txt::write.Y;
                px = txt::write.X;
            }
            
            const auto move = [&](){
                int pos = txt::write.X + (80*txt::write.Y);
                txt::graf::setpx(scrn[pos], txt::write.X, txt::write.Y);
            };
            if(dr){
                screen[txt::write.X + (txt::write.Y*80)] = cscr;
                for (int i = 0; i < 2000; i++) {
                    scrn[i] = screen[i];
                }
            }
            paint = ws.stread();
            switch (paint) {
                case var::shp:
                    dr = true;
                    break;
                case var::shb:
                    dr = false;
                    break;
                case var::w:
                    cscr += 0x10;
                    break;
                case var::s:
                    cscr -= 0x10;
                    break;
                case var::up:
                    move();
                    if (txt::write.Y > 0) {
                        txt::write.Y--;
                    }
                    else {
                        txt::write.Y = 24;
                    }
                    break;
                case var::dw:
                    move();
                    if (txt::write.Y < 24) {
                        txt::write.Y++;
                    }
                    else {
                        txt::write.Y = 0;
                    }
                    break;
                case var::esq:
                    move();
                    if (txt::write.X > 0) {
                        txt::write.X--;
                    }
                    else {
                        txt::write.X = 79;
                    }
                    break;
                case var::dir:
                    move();
                    if (txt::write.X < 79) {
                        txt::write.X++;
                    }
                    else {
                        txt::write.X = 0;
                    }
                    break;
                case var::esc:
                    cnt = false;
                    for (short i = 0; i<2000; i++){
                        fls::ils[n].pxs[i] = screen[i];
                    }
                    break;
                case var::sel:
                    screen[txt::write.X + (txt::write.Y*80)] = cscr;
                    break;
                default:
                    break;
            }
        }
    }
    void zmgfiles(){
        bool fs = true;
        int iot = 0;
        auto qnt = [&](){
            short i = 0;
            while (true) {
                if (fls::ils[i].name != NULL) {
                    i++;
                }
                else {
                    return i;
                }
            }
        };
        auto imgs = [&](){
            for(short i = 0; i < 33; i++){
                fls::ils[i].slc = false;
            }
            fls::ils[iot].slc = true;
            txt::graf::wall(cinzaCB);
            fls::listImg(fls::ils);
        };
        int par = qnt();
        imgs();
        while (fs) {
            var::setas mov = ws.stread();
            if (mov == var::nn) {
                continue;
            }
            switch (mov) {
                case var::dw:
                    if(iot <= (par - 10)){
                        iot+=10;
                    }
                    else {
                        iot = par - 1;
                    }
                    imgs();
                    break;
                case var::up:
                    if (iot >= 10) {
                        iot-=10;
                    }
                    else {
                        iot = 0;
                    }
                    imgs();
                    break;
                case var::dir:
                    if (iot >= par - 1) {
                        imgs();
                        break;
                    }
                    iot++;
                    imgs();
                    break;
                case var::esq:
                    if (iot <= 0) {
                        imgs();
                        break;
                    }
                    iot--;
                    imgs();
                    break;
                case var::sel:
                    fls::RIT(fls::ils, iot);
                    imgs();
                    break;
                case var::esc:
                    fs = false;
                    break;
                default:
                    break;
            }
        }
    }
    void Write(){
        txt::write.X = 5;
        txt::write.Y = 0;
        txt::graf::wall(vermelhoEB);
        var::ztring nm;
        txt::zio.setCor(amareloL + vermelhoEB);
        txt::zio<<"Name: ">>nm;
        short n = 0;
        for (; n < 33; n++) {
            if (fls::tls[n].name == nm ||  fls::tls[n].name == NULL) {
                break;
            }
        }
        char yn;
        txt::zio<<"Protected?[y/n]">>yn;
        if (yn == 'y') {
            fls::tls[n].prot = true;
        }
        if(n>=33){
            txt::zio<<"FULL";
            txt::zio<<"PRESS ANYTHING";
            ws.stread();
            return;
        }
        else {
            fls::tls[n].name = nm;
        }
        txt::graf::wall(blackout);
        txt::write.X = 5;
        txt::write.Y = 0;
        txt::zio.setCor(blackout+cianoCL);
        txt::zio<<fls::tls[n].content;
        var::ztring txt;
        while (!txt::zin.escp) {
            txt::zin.espcase = true;
            txt::zio>>fls::tls[n].content;
        }
        fls::tls[n].content.mem[fls::tls[n].content.size] = '\0';

        txt::zin.escp = false;
    }
    void zxtfiles(){
        bool mv = true;
        int io = 0;
        const auto qnt = [&](){
            for (short i = 0; i < 33; i++) {
                if (fls::tls[i].name == NULL) {
                    return i;
                }
            }
            return (short)33;
        };
        const auto zxts = [&](){
            for (short i = 0; i < 33; i++) {
                fls::tls[i].slc = false;
            }
            fls::tls[io].slc = true;
            txt::graf::wall(cinzaCB);
            fls::listTxt(fls::tls);
        };
        txt::graf::wall(cinzaCB);
        zxts();
        int par = qnt();
        while (mv) {
            var::setas mov = ws.stread();
            if (mov == var::nn) {
                continue;
            }
            switch (mov) {
                  case var::dw:
                    if(io <= (par - 10)){
                        io+=10;
                    }
                    else {
                        io = par - 1;
                    }
                    zxts();
                    break;
                case var::up:
                    if (io >= 10) {
                        io-=10;
                    }
                    else {
                        io = 0;
                    }
                    zxts();
                    break;
                case var::dir:
                    if (io >= par - 1) {
                        zxts();
                        break;
                    }
                    io++;
                    zxts();
                    break;
                case var::esq:
                    if (io <= 0) {
                        zxts();
                        break;
                    }
                    io--;
                    zxts();
                    break;
                case var::sel:
                    fls::RT(fls::tls, io);
                    txt::graf::wall(cinzaCB);
                    zxts();
                    break;
                case var::esc:
                    mv = false;
                    break;
                default:
                    break;
            }
        }
    }
    void filesmn(){
        auto str = [&](){
            txt::graf::wall(cianoCB);
            txt::graf::applist(arqop, 2, 5);
        };
        auto selec = [&](){
            switch (flpos) {
            case 0:
            Draw();
            break;
            case 1:
            zmgfiles();
            break;
            case 2:
            Write();
            break;
            case 3:
            zxtfiles();
            break;
            default:
            break;
            }
        };
        bool mn = true;
        arqop[0].nm = "Draw";
        arqop[1].nm = "Zimgs";
        arqop[2].nm = "Write";
        arqop[3].nm = "Texts";

        arqop[0].cor = brancoB;
        arqop[1].cor = cinzaCB;
        arqop[2].cor = verdeCB;
        arqop[3].cor = amareloB;
        
        short sv = -1;
        str();
        while (mn) {
            var::setas chs = ws.stread();
            switch (chs) {
                case var::up:
                if (flpos < 2) {
                    flpos = 0; break;
                }
                flpos -= 2;
                break;
                case var::dw:
                if (flpos > 1) {
                    flpos = 3; break;
                }
                flpos += 2;
                break;
                case var::dir:
                if (flpos >= 3) {
                    flpos = 3; break;
                }
                flpos++;
                break;
                case var::esq:
                if (flpos <= 0) {
                    flpos = 0; break;
                }
                flpos--;
                break;
                case var::esc:
                mn = false;
                break;
                case var::sel:
                selec();
                str();
                break;
                default:
                break;
            }
            if (flpos != sv) {
                sv = flpos;
                for (short i = 0; i < 4; i++) {
                    arqop[i].sel = false;
                }
                arqop[flpos].sel = true;
                txt::graf::applist(arqop, 2, 5);
            }
        }
    }
    public:
    int app = 0;
    void selec(){
        switch (app) {
            case 0:
                ter();
                break;
            case 1:
                calc();
                break;
            case 2:
                filesmn();
                break;
            case 3:
                Snake::Central();
                break;
            default:
                break;
        }
        ws.window();
    }
    void apsl(var::setas sl){
        switch (sl) {
            case var::sel:
                selec();
                break;
            case var::up:
                if (app < 2) {
                    break;
                }
                app-=2;
                break;
            case var::dw:
                if (app > 1){
                    break;
                }
                app+=2;
                break;
            case var::dir:
                if (app>=3) {
                    break;
                }
                app++;
                break;
            case var::esq:
                if (app<= 0) {
                    break;
                }
                app--;
                break;
            case var::w:
                if (var::delay <999999) {
                    var::delay += 9000;
                }
                break;
            case var::s:
                if (var::delay > 9000) {
                    var::delay -= 9000;
                }
                break;
            default:
                break;
        }
        ws.bar(app);
    }
}; funcs wks;
void init(){
    txt::write.vga = (volatile unsigned short*)0xB8000;
    txt::write.X = 0;
    txt::write.Y = 0;

    txt::graf::img.vga = (volatile unsigned short*)0xB8000;
    txt::graf::img.X = 0;
    txt::graf::img.Y = 0;
}
extern "C" void Tanya(){
    init();
    ws.window();
    ws.bar(0);
    while (true) {
        var::setas in = ws.stread();
        if (in != var::nn) {
            wks.apsl(in);
        }
    }
    return;
}