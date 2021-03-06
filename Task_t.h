//
// Created by user on 22.04.20.
//

#ifndef MULTITHREADAPP_TASKT_H
#define MULTITHREADAPP_TASKT_H

#include <iostream>
#include <map>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <memory>


/* other */
/* статусы для задач  */
// TODO: сделать через enum
const int TASK_WORKS = 1;
const int TASK_WAITING = 2;
const int TASK_PAUSE = 3;
const int TASK_END = 4;

enum class State {
	TASK_WORKS,
	TASK_WAITING,
	TASK_PAUSE,
	TASK_END
};


/*
 * Class describes object, that works in due std::thread, most of operations that made by functions
 * in MultiThread.cpp will be made as method in class.
 * Класс описывает объект, который будет при помощи std::thread, болшая часть операций, которые реализованы
 * в MultiThread.cpp через функции планируються быть реализованы через методы класса.
 */
class Task_t
{
private:

public:
//    std::shared_ptr<std::mutex> obj_mutex;              // use to get save thread access to object data / используться для доступа к текущему объекту
	// TODO: make some attributes atomic?
	std::mutex obj_mutex;
	time_t time_started;               // additng time of task время добавления задачи чтобы, отсчитывать и выводить время, через которое очнеться задача
    uint task_id;                      // is set by user / назначется вручную
    int delay_sec;                     // delay for starting of task / задержка запуска задачи
    int progress ;                     // progress of task / прогресс задачи
    State status;                      // code status: 0 - task is ending, 1 - in waiting, 2 - started, 3 - task in pause / код статуса: 0 - в процессе завершения, 1 - в ожидании, 2 - запущена, 3 - задача приостановлена
    bool in_proccess;                  // that status od task shows that one ot the tread is working with object / статус задачи, который говорит о том, что сейчас идет работа с текущем экзмемпляро задачи
    std::thread cur_thread;            // thread object for current task
//    int pause_flag (false);            // pause flag / флаг паузы потока, atomic флаг.

public:
    // TODO: necessarily make destructor 'cause I use smart pointer and thread is has to stopped correctly
    Task_t(uint id, int delay_sec);
//	Task_t(const Task_t &t) = delete;
//	Task_t & operator=(const Task_t&) = delete;\

    // thread function / поточная функция
    void thread_operations() ;
    // running thread / запуск задачи
	void run();

	// TODO: delete this function if it unused
	/*
	 * @brief return task id
	 * @return task id
	 */
	uint get_task_id() const;

	/*
	 * @brief generating info about task
	 * @return string info
	 */
	std::string get_task_info() const;

    // увидел такое использование в книге Уильямса "Параелельное программирование, эта перегруpзка
    // используеться для старта задачи, т.к. в std::thread можно передавать вызываемый объект
    void operator()();
};


#endif //MULTITHREADAPP_TASKT_H
