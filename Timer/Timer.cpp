#include <iostream>
#include <chrono>
#include <array>

class Timer
{
private:
	//startTime�����Ͷ���ע��
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
public:
	Timer()
	{
		//��ȡ��ʼʱ��
		startTime = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		stop();
	}

	void stop()
	{
		//��ȡ����ʱ��
		auto endTime = std::chrono::high_resolution_clock::now();
		//��startTimeǿת�ɺ���
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch().count();
		//��endTimeǿת�ɺ���
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();
		//����ʱ���
		auto duration = end - start;
		double ms = duration * 0.001;
		//��ӡ
		std::cout << duration << "us(" << ms << "ms)" << std::endl;
	}
};

int main()
{
	int value = 0;
	{
		Timer timer;
		for (int i = 0; i < 1000000; i++)
			value += 2;
	}

	//�Ƚ�unique_ptr��shared_ptr
	struct vector2
	{
		float x, y;
	};

	std::cout << "Make SharedPtrs\n";
	{
		//����ָ������
		std::array<std::shared_ptr<vector2>, 100> sharedPtrs;
		//��ʱ����ʼ
		Timer timer;
		for (int i = 0; i < sharedPtrs.size(); i++)
			sharedPtrs[i] = std::make_shared<vector2>();
	}

	std::cout << "New SharedPtrs\n";
	{
		//����ָ������
		std::array<std::shared_ptr<vector2>, 100> sharedPtrs;
		//��ʱ����ʼ
		Timer timer;
		for (int i = 0; i < sharedPtrs.size(); i++)
			sharedPtrs[i] = std::shared_ptr<vector2>(new vector2());
	}

	std::cout << "Make UniquePtrs\n";
	{
		//����ָ������
		std::array<std::unique_ptr<vector2>, 100> uniquePtrs;
		//��ʱ����ʼ
		Timer timer;
		for (int i = 0; i < uniquePtrs.size(); i++)
			uniquePtrs[i] = std::make_unique<vector2>();
	}

	std::cin.get();
}