// 2003 Guangzhou: Outernet
// ACM-ICPC Live Archive 2951
// POJ 1773

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <string>
using namespace std;
#define MAX 33000
#define OK 100
#define OKSELF 101
#define SEEND 200
#define UNKCMD 300
#define UNKDEST 301
#define NOBEG 302
#define NOLOOP 303
 
int plist[MAX];
int curport;
map<string, int> rtable;
void choutput(int port) {
    if (curport != port) {
        curport = port;
        printf("#%d\n", port);
    }
}
void msg(int port, int x) {
    choutput(port);
    printf("%d\n", x);
}
 
void init(int n) {
    int i;
    char cmd[100];
    rtable.clear();
    for (i = 0; i < n; i++) {
        int id;
        scanf("%s%d", cmd, &id);
        rtable[string(cmd)] = id;
    }
    memset(plist, -1, sizeof(plist));
    curport = -1;
    getchar();
}
 
char cmd[1000], data[50000];
void process_cmd() {
    int port = -1;
    while (1) {
        gets(cmd);
        if (cmd[0] == '#') {
            int tp = atoi(cmd + 1);
            if (tp < 0) {//退出
                printf("#-1\n");
                return;
            }
            port = tp;
        } else if (strstr(cmd, "TO:") == cmd) {
            string dest;
            int j = 3;
            while (cmd[j])
                dest += cmd[j++];//获取目标地名称
 
            if (rtable.find(dest) != rtable.end()) {//在路由表中查找地址
                if (rtable[dest] == port) msg(port, NOLOOP);//输入输出端口相同
                else {
                    if (plist[port] > 0) {//给原端口发送一个QUIT命令
                        choutput(plist[port]);
                        printf("QUIT\n");
                    }
                    plist[port] = rtable[dest];
                    if (plist[port] != 0) {//判断输出端口是否为proxy本身，若不是
                        choutput(plist[port]);
                        printf("%s\n", cmd);
                    }//返回一个信息给输入端口
                    if (plist[port] != 0) msg(port, OK);
                    else msg(port, OKSELF);
                }
            } else msg(port, UNKDEST);//找不到
        } else if (strcmp("DATA", cmd) == 0) {//收到DATA命令
            char ch;//先处理数据流
            int i = 0;
            while ((ch = getchar()) != '.') {
                if (ch == '\\') {
                    data[i++] = ch;
                    ch = getchar();
                }
                data[i++] = ch;
            }
            data[i++] = ch;
            data[i] = 0;
            getchar();
            if (plist[port] != -1) {//如果已经和某个端口建立了链接
                if (plist[port] != 0) {//判断输出端口是否为proxy本身，若不是
                    choutput(plist[port]);
                    printf("%s\n", cmd);
                    printf("%s\n", data);
                }
                if (plist[port] != 0) msg(port, OK);
                else msg(port, OKSELF);
            } else msg(port, NOBEG);//没有建立Session
        } else if (strcmp("QUIT", cmd) == 0) {//收到退出命令
            if (plist[port] == -1) {
                msg(port, NOBEG);
            } else {
                if (plist[port] != 0) {//判断输出端口是否为proxy本身，若不是
                    choutput(plist[port]);
                    printf("%s\n", cmd);
                }
                msg(port, SEEND);
                plist[port] = -1;
            }
        } else msg(port, UNKCMD);//不知道当前命令
    }
}
 
int main() {
    int n;
    while (scanf("%d", &n) && n != 0) {
        init(n);
        process_cmd();
    }
    return 0;
}