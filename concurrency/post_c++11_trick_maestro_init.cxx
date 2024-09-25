class myclass;

my_class& get_my_class_instance() {
  /*
        With the advent of the C++11 compiler, the initialization of static variables is defined to be executed in only one thread, and no other threads will continue executing until this initialization is complete.
  */ 
  static my_class instance;
  return instance;
}
