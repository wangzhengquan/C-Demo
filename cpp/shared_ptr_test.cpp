#include "comm_inc.h"
#include <bitset>
#include <memory>

using namespace std;

struct Foo
{
  int id{0};
  int id2{0};
  // Foo(int i = 0, int j=0) : id{i}, id2{j} { std::cout << "Foo::Foo(int, int), id=" << id << "\n"; }
  Foo(int i = 0) : id{i} { std::cout << "Foo::Foo(int), id=" << id << "\n"; }
  Foo(Foo& foo) : id{foo.id}{ std::cout << "Foo::Foo(Foo&), id=" << id << "\n"; }
  Foo(Foo&& foo) : id{std::move(foo.id)}{ std::cout << "Foo::Foo(Foo&&), id=" << id << "\n"; }
  ~Foo() { std::cout << "Foo::~Foo(), id=" << id << '\n'; }
};


class Buffer {
  private:
    std::shared_ptr<Foo> foo_ptr{};

  public:
    Buffer() = default;

    Buffer(std::shared_ptr<Foo> other_foo_ptr): foo_ptr(move(other_foo_ptr)){
      // count++;
      std::cout << "Buffer::Buffer(std::shared_ptr<Foo>): id=" << foo_ptr->id  << "\n";
    }

    // Buffer(std::shared_ptr<Foo> &other_foo_ptr): foo_ptr(other_foo_ptr){
    //   // count++;
    //   std::cout << "Buffer::Buffer(std::shared_ptr<Foo>&): id=" << foo_ptr->id  << "\n";
    // }
    //! \brief Construct by taking ownership of a string
    Buffer(Foo &foo) noexcept : foo_ptr(std::make_shared<Foo>(foo)) {
      // count++;
      std::cout << "Buffer::Buffer(Foo&): id=" << foo_ptr->id  << "\n";
    }

    Buffer(Foo *foo) noexcept : foo_ptr(foo) {
      // count++;
      std::cout << "Buffer::Buffer(Foo*): id=" << foo_ptr->id  << "\n";
    }

    ~Buffer(){
      //count--;
      std::cout << "Buffer::~Buffer(), id=" << foo_ptr->id  << '\n';
    }
};


int main(int argc, char *argv[])
{
  {
    std::cout << "0)- shared_ptr as parameter-------------\n";
    std::shared_ptr<Foo> shptr(new Foo{10});
    Buffer buffer(shptr);
  }

  {
    std::cout << "1) constructor shared_ptr\n";
    std::shared_ptr<Foo> sh1(new Foo{10});
    std::cout << "sh2.use_count(): " << sh1.use_count() << '\n';

    std::shared_ptr<Foo> sh2(sh1);
    std::cout << "sh1.use_count(): " << sh1.use_count() << '\n';
    std::cout << "sh2.use_count(): " << sh2.use_count() << '\n';

    std::shared_ptr<Foo> sh3;
    sh3 = sh1;
    std::cout << "sh1.use_count(): " << sh1.use_count() << '\n';
    std::cout << "sh2.use_count(): " << sh2.use_count() << '\n';
    std::cout << "sh3.use_count(): " << sh3.use_count() << '\n';
  }

  {
    std::cout << "2) Queue\n";
    Foo foo{1};
    std::cout << "--- create queue\n";
    std::queue<Buffer> queue{};
    std::cout << "--- push\n";
    queue.push(Buffer{foo});
    queue.push(Buffer{new Foo(2)});
    std::cout << "--- pop\n";
    queue.pop();
    queue.pop();

    std::cout << "----end\n";
  }

  {
    std::cout << "1) Unique ownership semantics demo\n";
    std::unique_ptr<Foo> foo =  std::make_unique<Foo>(1);
    foo =  std::make_unique<Foo>(2);
    std::unique_ptr<Foo> foo2 = std::move(foo); 
    foo2 = std::move(foo2);
    std::cout << "----end\n";
  }

  // {
  //   Foo foo{1, 2};
  //   std::cout << foo.id << "," << foo.id2 <<  "\n";
  // }
}
