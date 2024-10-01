
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <windows.h>
//Пример создания и управления потоком:
/*
void task() {
    std::cout << "Task is running in thread: " << std::this_thread::get_id() << std::endl;
}

int main() {
    std::thread t(task);  // Создание потока и запуск функции task
    std::cout << "Main thread: " << std::this_thread::get_id() << std::endl;

    t.join();  // Ожидание завершения потока t
    return 0;
}
*/

//Примеры работы с мьютексом
/*
std::mutex mtx;

void print_task(int n) {
    std::lock_guard<std::mutex> lock(mtx);  // Блокировка мьютекса для защиты критической секции
    std::cout << "Thread " << std::this_thread::get_id() << " is printing: " << n << std::endl;
}

int main() {
    std::thread t1(print_task, 1);
    std::thread t2(print_task, 2);

    t1.join();
    t2.join();

    return 0;
}
*/
/*Управление приоритетами потоков*/
/*
void task() {
    std::cout << "Task running in thread: " << GetCurrentThreadId() << std::endl;
}

int main() {
    std::thread t(task);
    
    // Установка приоритета потока
    SetThreadPriority(t.native_handle(), THREAD_PRIORITY_HIGHEST);
    
    t.join();
    return 0;
}
*/
//Пример с использованием условной переменной

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_task(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready; });  // Ожидание сигнала о готовности
    std::cout << "Thread " << id << " is running\n";
}

void set_ready() {
    std::unique_lock<std::mutex> lock(mtx);
    ready = true;
    cv.notify_all();  // Уведомление всех потоков
}

int main() {
    std::thread t1(print_task, 1);
    std::thread t2(print_task, 2);

    std::this_thread::sleep_for(std::chrono::seconds(1));  // Имитация работы
    set_ready();  // Установка готовности и уведомление потоков

    t1.join();
    t2.join();

    return 0;
}


