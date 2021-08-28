#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "myproto.pb.h"
using namespace std;
//bool SerializeToString(string* output) const;  
//bool ParseFromString(const string& data); 

string str; //全局变量

void set_person()//类似于request,设置好各个参数，然后SerializeToString，发送给server
{
    Person obj;
    obj.set_name("mike");
    obj.set_id(1);
    //obj.set_email("xxx@qq.com");
    *obj.mutable_email() = "xxx@qq.com";

    obj.SerializeToString(&str);    //序列化，obj成员的内容设置给str
}

void get_person() //类似于response,从server获取后，ParseFromString反序列化，得出各个参数的结果
{
    Person obj;
    obj.ParseFromString(str); //反序列化, str内容设置给obj的成员

    cout << "name = " << obj.name() << endl;
    cout << "id = " << obj.id() << endl;
    cout << "email = " << *obj.mutable_email() << endl;//这两种写法效果相同
    cout << "email = " << obj.email() << endl;//这两种写法效果相同
    cout << "phone = " << *obj.mutable_phone() << endl;
    cout << "has_phone1 = " << obj.has_phone1() << endl;
    cout << "has_phone = " << obj.has_phone() << endl;

}
void set_addressbook()
{
    AddressBook obj;

    Person *p1 = obj.add_people(); //新增加一个Person
    p1->set_name("mike");
    p1->set_id(1);
    p1->set_email("mike@qq.com");

    Person *p2 = obj.add_people(); //新增加一个Person
    p2->set_name("jiang");
    p2->set_id(2);
    p2->set_email("jiang@qq.com");

    Person *p3 = obj.add_people(); //新增加一个Person
    p3->set_name("abc");
    p3->set_id(3);
    p3->set_email("abc@qq.com");


    bool flag = obj.SerializeToString(&str);//序列化

}

void get_addressbook()
{
    AddressBook obj;
    obj.ParseFromString(str);  //反序列化

    for (int i = 0; i < obj.people_size(); i++)
    {
        const Person& person = obj.people(i);//取第i个people
        cout << "第" << i + 1 << "个信息\n";
        cout << "name = " << person.name() << endl;
        cout << "id = " << person.id() << endl;
        cout << "email = " << person.email() << endl << endl;
    }
}
int main(int argc, char* argv[])
{
    set_person(); //序列化
    get_person(); //反序列化
    cout << "++++++++++++++++++分界线++++++++++++++++++++++"<< endl;

    set_addressbook();
    get_addressbook();

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}


//编译命令
//g++ test.cpp  myproto.pb.cc  -o test `pkg-config --libs --cflags protobuf`
