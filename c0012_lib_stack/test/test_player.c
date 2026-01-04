#include "test_player.h"

// extern关键字不可以与static同时使用
NODE *kobe_node = NULL;
NODE *jordan_node = NULL;
NODE *yao_node = NULL;
NODE *yi_node = NULL;
NODE *camelo_node = NULL;
NODE *dunken_node = NULL;
NODE *curry_node = NULL;
NODE *jimmy_node = NULL;
NODE *book_node = NULL;
NODE *paul_node = NULL;
NODE *rodman_node = NULL;
NODE *jokic_node = NULL;

void init_data() {
  /* initial the player node.*/

  kobe_node = (NODE *)malloc(sizeof(NODE));
  PLAYER *kobe = (PLAYER *)malloc(sizeof(PLAYER));
  kobe_node->ptr_data = kobe;
  kobe->tm = (TEAM *)malloc(sizeof(TEAM));
  kobe->pname = "Kobe", kobe->pnumber = 8, kobe->salary = 3500;
  kobe->tm->tname = "Lakers", kobe->tm->city = "LA";
  // TEAM tm_LA = {.tname = "Lakers", .city = "LA"};
  // PLAYER kobe = {.pname = "Kobe", .pnumber = 8, .salary = 3500, .tm =
  // &tm_LA};

  jordan_node = (NODE *)malloc(sizeof(NODE));
  PLAYER *jordan = (PLAYER *)malloc(sizeof(PLAYER));
  jordan_node->ptr_data = jordan;
  jordan->tm = (TEAM *)malloc(sizeof(TEAM));
  jordan->pname = "Jordan", jordan->pnumber = 23, jordan->salary = 3000;
  jordan->tm->tname = "Bulls", jordan->tm->city = "Chicago";

  // 这种写法在本案中会有问题，初始化的pnumber和salary数据在程序运行中会改变，或者在打印player成员值的时候会报指针指向了非法
  // 原因可能是ptr_data是一个void指针，这种初始化方式分配的地址在后来的node结构体中无法访问
  // TEAM tm_CH = {"Bulls", "Chicago"};
  // PLAYER jordan = {.pname = "Michael", .pnumber = 23, .salary = 3000, .tm =
  // &tm_CH};

  yao_node = (NODE *)malloc(sizeof(NODE));
  PLAYER *yao = (PLAYER *)malloc(sizeof(PLAYER));
  yao_node->ptr_data = yao;
  yao->tm = (TEAM *)malloc(sizeof(TEAM));
  yao->pname = "Yao", yao->pnumber = 11, yao->salary = 2500;
  yao->tm->tname = "Rockets", yao->tm->city = "Hous";

  yi_node = (NODE *)malloc(sizeof(NODE));
  PLAYER *yi = (PLAYER *)malloc(sizeof(PLAYER));
  yi_node->ptr_data = yi;
  yi->tm = (TEAM *)malloc(sizeof(TEAM));
  yi->pname = "Yi", yi->pnumber = 6, yi->salary = 500;
  yi->tm->tname = "Bucks", yi->tm->city = "Milv";

  camelo_node = (NODE *)malloc(sizeof(NODE));
  PLAYER *camelo = (PLAYER *)malloc(sizeof(PLAYER));
  camelo_node->ptr_data = camelo;
  camelo->tm = (TEAM *)malloc(sizeof(TEAM));
  camelo->pname = "Camelo", camelo->pnumber = 15, camelo->salary = 2700;
  camelo->tm->tname = "Nick", camelo->tm->city = "NY";

  dunken_node = (NODE *)malloc(sizeof(NODE));
  PLAYER *dunken = (PLAYER *)malloc(sizeof(PLAYER));
  dunken_node->ptr_data = dunken;
  dunken->tm = (TEAM *)malloc(sizeof(TEAM));
  dunken->pname = "Tim", dunken->pnumber = 21, dunken->salary = 3200;
  dunken->tm->tname = "Spurs", dunken->tm->city = "Santo";

  curry_node = (NODE *)malloc(sizeof(NODE));
  PLAYER *curry = (PLAYER *)malloc(sizeof(PLAYER));
  curry_node->ptr_data = curry;
  curry->tm = (TEAM *)malloc(sizeof(TEAM));
  curry->pname = "Curry", curry->pnumber = 30, curry->salary = 5000;
  curry->tm->tname = "War", curry->tm->city = "San";

  jimmy_node = (NODE *)malloc(sizeof(NODE));
  PLAYER *jimmy = (PLAYER *)malloc(sizeof(PLAYER));
  jimmy_node->ptr_data = jimmy;
  jimmy->tm = (TEAM *)malloc(sizeof(TEAM));
  jimmy->pname = "Jimmy", jimmy->pnumber = 10, jimmy->salary = 5500;
  jimmy->tm->tname = "War", jimmy->tm->city = "San";

  book_node = (NODE *)malloc(sizeof(NODE));
  PLAYER *book = (PLAYER *)malloc(sizeof(PLAYER));
  book_node->ptr_data = book;
  book->tm = (TEAM *)malloc(sizeof(TEAM));
  book->pname = "Book", book->pnumber = 0, book->salary = 3800;
  book->tm->tname = "Suns", book->tm->city = "Phix";

  paul_node = (NODE *)malloc(sizeof(NODE));
  PLAYER *paul = (PLAYER *)malloc(sizeof(PLAYER));
  paul_node->ptr_data = paul;
  paul->tm = (TEAM *)malloc(sizeof(TEAM));
  paul->pname = "Paul", paul->pnumber = 3, paul->salary = 4000;
  paul->tm->tname = "Suns", paul->tm->city = "Phix";

  rodman_node = (NODE *)malloc(sizeof(NODE));
  PLAYER *rodman = (PLAYER *)malloc(sizeof(PLAYER));
  rodman_node->ptr_data = rodman;
  rodman->tm = (TEAM *)malloc(sizeof(TEAM));
  rodman->pname = "Rodman", rodman->pnumber = 91, rodman->salary = 1000;
  rodman->tm->tname = "Piston", rodman->tm->city = "Dix";

  jokic_node = (NODE *)malloc(sizeof(NODE));
  PLAYER *jokic = (PLAYER *)malloc(sizeof(PLAYER));
  jokic_node->ptr_data = jokic;
  jokic->tm = (TEAM *)malloc(sizeof(TEAM));
  jokic->pname = "Jokic", jokic->pnumber = 15, jokic->salary = 6000;
  jokic->tm->tname = "Nug", jokic->tm->city = "Den";

  /* player node initialized complete.*/
}

void test_data_structure(Stack *stack) {
  int print_count = 0;
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_stack(stack);

  push(stack, jordan_node);

  push(stack, jokic_node);

  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_stack(stack);

  pop(stack);

  push(stack, yi_node);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_stack(stack);

  push(stack, rodman_node);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_stack(stack);

  push(stack, jimmy_node);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_stack(stack);

  push(stack, book_node);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_stack(stack);

  pop(stack);

  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_stack(stack);

  pop(stack);
  pop(stack);
  pop(stack);

  push(stack, kobe_node);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_stack(stack);

  push(stack, yao_node);
  pop(stack);
  pop(stack);
  pop(stack);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_stack(stack);

  pop(stack);

  push(stack, dunken_node);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_stack(stack);

  push(stack, paul_node);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_stack(stack);

  push(stack, book_node);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_stack(stack);

  push(stack, jordan_node);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_stack(stack);

  push(stack, camelo_node);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_stack(stack);

  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  push(stack, curry_node);
  push(stack, jimmy_node);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_stack(stack);

  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);

  pop(stack);
  pop(stack);
  pop(stack);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_stack(stack);

  pop(stack);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_stack(stack);

  pop(stack);
  pop(stack);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_stack(stack);

  push(stack, kobe_node);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_stack(stack);

  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  pop(stack);
  push(stack, rodman_node);
  push(stack, book_node);
  push(stack, jokic_node);
  push(stack, jimmy_node);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_stack(stack);
  pop(stack);
  pop(stack);
  printf("~~~~~~~~~~~~~~~~~print count: %d~~~~~~~~~~~~~~~~~~~~~~~\n",
         print_count++);
  print_stack(stack);

  free(kobe_node);
  free(jordan_node);
  free(yao_node);
  free(yi_node);
  free(curry_node);
  free(rodman_node);
  free(jimmy_node);
  free(book_node);
  free(paul_node);
  free(camelo_node);
  free(dunken_node);
  free(jokic_node);
}
