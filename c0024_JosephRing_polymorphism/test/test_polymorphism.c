#include "test_polymorphism.h"

TestResult test_polymorphism() {
  Linkedlist *llist = create_linkedlist();
  linkedlist_constructor(llist, NULL, NULL, 0, NULL, NULL, &destroy_linkedlist,
                         "Linkedlist", &set_name_ll, &get_name_ll,
                         &ll_toString);

  SingleLinkedlist *sll = create_single_linkedlist();
  single_linkedlist_constructor(sll, NULL, NULL, 0, "Narcissus",
                                &insert_node_sll, &delete_node_sll,
                                &destroy_single_linkedlist, "SingleLinkedlist",
                                &set_name_sll, &get_name_sll, &sll_toString);

  SCLinkedlist *scll = create_single_circular_linkedlist();
  single_circular_linkedlist_constructor(
      scll, NULL, NULL, 0, &insert_node_scll, &delete_node_scll,
      &destroy_single_circular_linkedlist, "SCLinkedlist", &set_name_scll,
      &get_name_scll, &scll_toString);

  DoubleLinkedList *dll = create_double_linkedlist();
  double_linkedlist_constructor(dll, NULL, NULL, 0, 'K', &insert_node_dll,
                                &delete_node_dll, &destroy_double_linkedlist,
                                "DoubleLinkedList", &set_name_dll,
                                &get_name_dll, &dll_toString);

  DCLinkedList *dcll = create_double_circular_linkedlist();
  double_circular_linkedlist_constructor(
      dcll, "dcll polymorphism", "0123", NULL, NULL, 0, &insert_node_dcll,
      &delete_node_dcll, &destroy_double_circular_linkedlist, "DCLinkedList",
      &set_name_dcll, &get_name_dcll, &dcll_toString);

  llist->toString(llist);
  llist->toString(sll);
  llist->toString(scll);
  // DoubleLinkedList和DCLinkedlist的结构体第一个成员不是Linkedlist对象，所以无法通过继承实现多态
  // 下面这种写法会报错
  // llist->toString(dll);
  // llist->toString(dcll);
  // 必须指向各自结构体中的父类指针，才能正确实现继承和多态
  llist->toString(dll->super);
  llist->toString(dcll->super);

  llist->destroy_ll(sll);
  llist->destroy_ll(scll);
  // 作为sll和scll两个对象的父类，要在子类释放之后再十分哪个，否则会有空间释放错误（Invalide
  // read of size 8）
  llist->destroy_ll(llist);
  dll->super->destroy_ll(dll);
  dcll->super->destroy_ll(dcll);

  return TEST_PASSED;
}
