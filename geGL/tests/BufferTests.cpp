#include<catch.hpp>
#include<SDLWin.h>
#include<geGL/geGL.h>

using namespace ge::gl;
using namespace std;

TEST_CASE("Buffer Tests"){
  SDLWin win;
  win.beginFrame();
  ge::gl::init();
  {
    float data[4] = {1.f,2.f,3.f,4.f};
    auto b = make_shared<Buffer>(4*sizeof(float),data);
    REQUIRE(b->getSize() == 4*sizeof(float));
    data[0] = data[1] = data[2] = data[3] = 0.f;
    b->getData(data);
    REQUIRE(data[0] == 1.f);
    REQUIRE(data[1] == 2.f);
    REQUIRE(data[2] == 3.f);
    REQUIRE(data[3] == 4.f);
    data[0] = data[1] = data[2] = data[3] = 10.f;
    b->setData(data);
    data[0] = data[1] = data[2] = data[3] = 0.f;
    b->getData(data);
    REQUIRE(data[0] == 10.f);
    REQUIRE(data[1] == 10.f);
    REQUIRE(data[2] == 10.f);
    REQUIRE(data[3] == 10.f);
    data[0] = data[1] = data[2] = data[3] = 100.f;
    b->setData(data,sizeof(float)*2,sizeof(float)*2);
    data[0] = data[1] = data[2] = data[3] = 0.f;
    b->getData(data);
    REQUIRE(data[0] == 10.f);
    REQUIRE(data[1] == 10.f);
    REQUIRE(data[2] == 100.f);
    REQUIRE(data[3] == 100.f);
    auto c = make_shared<Buffer>(3*sizeof(float));
    c->copy(*b);
    data[0] = data[1] = data[2] = data[3] = 0.f;
    c->getData(data);
    REQUIRE(data[0] == 10.f);
    REQUIRE(data[1] == 10.f);
    REQUIRE(data[2] == 100.f);
    REQUIRE(data[3] == 0.f);
    auto oldId = c->getId();
    c->realloc(10*sizeof(float),Buffer::KEEP_DATA_ID);
    REQUIRE(c->getSize() == 10*sizeof(float));
    REQUIRE(c->getId() == oldId);
    float dd[10];
    for(int i=0;i<10;++i)dd[i] = 0.f;
    c->getData(dd);
    REQUIRE(dd[0] == 10.f);
    REQUIRE(dd[1] == 10.f);
    REQUIRE(dd[2] == 100.f);
    oldId = c->getId();
    c->realloc(sizeof(float),Buffer::KEEP_ID);
    REQUIRE(c->getSize() == sizeof(float));
    REQUIRE(c->getId() == oldId);
  }
  win.endFrame();
}

TEST_CASE("BufferSize"){
  SDLWin win;
  win.beginFrame();
  ge::gl::init();
  {
    std::cerr << "sizeof(GLsizeiptr): " << sizeof(GLsizeiptr) << std::endl;
    size_t const size = 1024ull*1024ull*1024ull*3ull;
    auto b = make_shared<Buffer>(size);
    REQUIRE(b->getSize() == size);
  }
  win.endFrame();
}
