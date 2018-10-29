#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable> 

int counter = 0;
int maxSize = 30;
std::mutex mtx;
std::queue<int> dataQuene; // �������ߺ������߹��� 
std::condition_variable producer, consumer;  // ����������һ��ͬ�����ƣ�Ҫ��mutex�Լ�lockһ��ʹ�� 

void func_consumer()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));// �����߱���������
        std::unique_lock<std::mutex> lck(mtx);
        consumer.wait(lck, [] {return dataQuene.size() != 0; });     // �����������ȴ��� ֱ��������Ԫ�ظ�������0
        int num = dataQuene.front();
        dataQuene.pop();
        std::cout << "consumer " << std::this_thread::get_id() << ": " << num << std::endl;
        producer.notify_all();                                       // ֪ͨ�����ߵ�������Ԫ�ظ���С��maxSize
    }
}


void func_producer()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(900));  // ��������΢�������߿�
        std::unique_lock<std::mutex> lck(mtx);
        producer.wait(lck, [] {return dataQuene.size() != maxSize; });// �����������ȴ��� ֱ��������Ԫ�ظ���С��maxSize
        ++counter;
        dataQuene.push(counter);
        std::cout << "producer " << std::this_thread::get_id() << ": " << counter << std::endl;
        consumer.notify_all();                                        //֪ͨ�����ߵ������е�Ԫ�ظ�������0
    }
}


int testSmartPoint_main()
{
    std::thread consumers[2], producers[2];

    // ���������ߺ�������
    for (int i = 0; i < 2; ++i)
    {
        consumers[i] = std::thread(func_consumer);
        producers[i] = std::thread(func_producer);
    }

    for (int i = 0; i < 2; ++i)
    {
        producers[i].join();
        consumers[i].join();
    }

    system("pause");
    return 0;
}