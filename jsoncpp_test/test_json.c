#include <iostream>
#include <sstream>
#include <fstream>
#include "usg_common.h"
#include <jsoncpp/json.h>

void readJsonFromFile()
{
  std::ifstream ifs;
  ifs.open("test.json");
  std::stringstream buffer;
  buffer << ifs.rdbuf();
  ifs.close();

  auto str = buffer.str();

  Json::Reader reader;
  Json::Value value;
  if (reader.parse(str, value))
  {
    //节点判断
    std::cout << "value's empty:" << value.empty() << std::endl;
    std::cout << "name is string:" << value["name"].isString() << std::endl;
    std::cout << "age is string:" << value["age"].isString() << std::endl;

    //类型获取
    std::cout << "name's type:" << value["name"].type() << std::endl;
    std::cout << "like's type:" << value["like"].type() << std::endl;

    //类型转换
    //根据Key获取值时最好判断类型,否则解析会中断
    std::cout << "name:" << value["name"].asString() << std::endl;
    std::cout << "age:" << value["age"].asInt() << std::endl;

    //节点获取
    std::cout << value["job"] << std::endl;                        //[]方式获取
    std::cout << value.get("name", "dxx") << std::endl;            //get方式获取
    std::cout << value.isMember("job") << std::endl;
    std::cout << "value's obj:" << value.isObject() << std::endl;
    std::cout << "like's obj:" << value["like"].isObject() << std::endl;
    std::cout << "like.size:" << value["like"].size() << std::endl;
    std::cout << "like[0][food]:" << value["like"][0]["food"].asString() << std::endl;

    //节点操作
    std::cout << "name compare age:" << value["name"].compare("age") << std::endl;
    value["name"] = "swduan";            //修改
    value["address"] = "hz";             //增加
    value["phone"] = "10086";
    value.removeMember("age");           //删除
    value["like"][0]["sport"] = "game";  //往value["like"]中添加一项元素

    Json::Value item;
    item["hate"] = "game";
    value["like"].append(item);            //value["like"]中再添加一维数组
    std::cout << "value[\"like\"]'s size:" << value["like"].size() << std::endl;

    std::cout << "--------------------" << std::endl;
    std::cout << value.toStyledString() << std::endl;

    std::cout << "--------------------" << std::endl;
    auto all_member = value.getMemberNames();
    for (auto member : all_member)
    {
      std::cout << member << std::endl;
    }

    std::cout << "--------------------" << std::endl;
    value.clear();        //清空元素
    std::cout << value.toStyledString() << std::endl;
  }
}

void jsonWriteToFile()
{
  //Json::FastWriter write;
  Json::Value root;

  Json::Value item;
  Json::Value arrayObj;
  item["book"] = "c++";
  item["food"] = "apple";
  item["music"] = "ddx";
  arrayObj.append(item);

  root["name"] = "dsw";
  root["age"]  = 18;
  root["like"] = arrayObj;    //注意:这里不能用append,append功能是将Json::Value添加到数组末尾

  auto str = root.toStyledString();
  std::cout << str << std::endl;

  std::ofstream ofss;
  ofss.open("test.json");
  ofss << str;
  ofss.close();
}

void jsonReadAndWrite()
{
  std::string kucker_data_file = "test2.json";
  Json::Value root;

  Json::Reader jsonreader;
  std::ifstream fin(kucker_data_file);
  if (fin)
  {
    if(!jsonreader.parse(fin, root)) {
      err_msg(0, "parse false");
    }
    fin.close();
  }
// printf("==============2\n");
  Json::Value infojson;
  infojson["id"] = "1";
  infojson["name"] = "kucker1";
  infojson["pid"] = 9882;
  infojson["command"] = "bash -l";
  infojson["create_time"] = (int)time(0);
  infojson["status"] = 1;
  infojson["volume"] = "/a:/b";
  root.append(infojson);

  infojson["id"] = "2";
  infojson["name"] = "kucker2";
  infojson["pid"] = 23424;
  infojson["command"] = "ls -l";
  infojson["create_time"] = (int)time(0);
  infojson["status"] = 2;
  infojson["volume"] = "/aaa:/ccc";
  root.append(infojson);

  auto str = root.toStyledString();
  std::cout << str << std::endl;
  std::ofstream fout;
  fout.open(kucker_data_file);
  fout << str;
  fout.close();
}

int main()
{
  //jsonWriteToFile();
 // readJsonFromFile();
  jsonReadAndWrite();

  // getchar();
  return 0;
}
