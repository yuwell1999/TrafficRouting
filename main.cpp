#include<iostream>
using namespace std;
#include"G_City.h"
#include <stdlib.h>
//声明湖南城市图结构
G_City Hunan;

void Handle();

//管理者操作页面
void Adm()
{
    int a;
    cout << "**********欢迎进入网络交通查询系统！**********\n" << endl;
    while (1)
    {
        string na1, na2;
        cout << "\t\t操作选项" << endl << endl;
        cout << "\t1\t初始化网络图" << endl;
        cout << "\t2\t修改信息" << endl;
        cout << "\t3\t增加线路" << endl;
        cout << "\t4\t删除线路" << endl;
        cout << "\t5\t增加城市" << endl;
        cout << "\t6\t删除城市" << endl;
        cout << "\t7\t用户页面" << endl;
        cout << "\t0\t返回页面" << endl;
        cout << " 请选择您需要的服务（输入相应数字代号）：";
        cin >> a;
        system("cls");
        switch (a)
        {
            case 1:
                Init_G(Hunan); break;

            case 2:
                Rev(Hunan); break;
            case 3:
                cout << "请输入需要增加线路的两个城市：" << endl;
                cin >> na1 >> na2;
                Add_Arc(Hunan, na1, na2);
                Print(Hunan);
                break;
            case 4:
                cout << "请输入需要删除之间线路的两个城市：" << endl;
                cin >> na1 >> na2;
                Del_Arc(Hunan, na1, na2);
                Print(Hunan);
                break;
            case 5:
                Add_C(Hunan);
                Print(Hunan);
                break;
            case 6:
                Del_C(Hunan);
                Print(Hunan);
                break;

            case 7:
                User(); break;
            case 0:
                return;
            default:
                cout << "输入有误，请重新选择！" << endl;  break;
        }
        system("pause");
        system("cls");

    }
}

//用户操作界面
void User()
{

    int a;
    while (1)
    {
        cout << "**********欢迎使用余越开发的网络交通查询系统！V1.0**********\n" << endl;
        cout << "\t\t本系统提供以下功能：" << endl;
        cout << "\t1\t打印网络图" << endl;
        cout << "\t2\t查询城市信息" << endl;
        cout << "\t3\t查询指定城市信息" << endl;
        cout << "\t4\t查询任意城市信息" << endl;
        cout << "\t0\t返回" << endl;
        cout << " 请选择您需要的功能：";
        cin >> a;
        switch (a)
        {
            case 1:
                Print(Hunan);
                break;
            case 2:
                Find_C(Hunan);
                break;
            case 3:
                Find_S1(Hunan);
                break;
            case 4:
                Find_S2(Hunan);
                break;
            case 0:cout << "返回页面" << endl;return;
            default:cout << "输入有误，请重新选择！" << endl; break;
        }
        cout << endl << "*******************************************" << endl;
        system("pause");
        system("cls");
    }
}

//操作页面
void Handle()
{
    cout << "**********欢迎使用余越开发的网络交通查询系统！V1.0 **********" << endl<<endl;
    int a;    //记录用户选择服务选项
    string pw;
    while (1)
    {
        cout << "\t请问您想以什么身份使用系统？" <<endl<< "\t1\t后台管理人员"<<endl<<"\t2\t用户"<<endl<<"\t0\t退出系统"<<endl<<endl;
        cout <<"\t请在此输入："<<endl<<endl;
        cin >> a;
        switch (a)
        {
            case 1:
                cout << "请输入管理后台密码：" << endl;

                cin >> pw;
                if (pw == "BlackSheepWall")
                {
                    system("cls");
                    Adm();
                }else
                {
                    cout << "密码错误！" << endl;
                    getchar();
                    continue;
                }
                break;
            case 2:
                system("cls"); User(); break;
            case 0:cout << "感谢您的支持，欢迎下次继续使用！" << endl; exit(01);
            default:cout << "请选择正确的序号！" << endl;
                    system("pause");
                    system("cls");
                    break;
        }
    }
}

int main() {
    Handle();
    return 0;
}