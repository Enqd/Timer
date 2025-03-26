#include <iostream>
#include <chrono>
#include <array>

class Timer
{
private:
	//startTime的类型定义注意
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
public:
	Timer()
	{
		//获取开始时间
		startTime = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		stop();
	}

	void stop()
	{
		//获取结束时间
		auto endTime = std::chrono::high_resolution_clock::now();
		//将startTime强转成毫秒
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch().count();
		//将endTime强转成毫秒
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();
		//计算时间差
		auto duration = end - start;
		double ms = duration * 0.001;
		//打印
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

	//比较unique_ptr和shared_ptr
	struct vector2
	{
		float x, y;
	};

	std::cout << "Make SharedPtrs\n";
	{
		//创建指针数组
		std::array<std::shared_ptr<vector2>, 100> sharedPtrs;
		//计时器开始
		Timer timer;
		for (int i = 0; i < sharedPtrs.size(); i++)
			sharedPtrs[i] = std::make_shared<vector2>();
	}

	std::cout << "New SharedPtrs\n";
	{
		//创建指针数组
		std::array<std::shared_ptr<vector2>, 100> sharedPtrs;
		//计时器开始
		Timer timer;
		for (int i = 0; i < sharedPtrs.size(); i++)
			sharedPtrs[i] = std::shared_ptr<vector2>(new vector2());
	}

	std::cout << "Make UniquePtrs\n";
	{
		//创建指针数组
		std::array<std::unique_ptr<vector2>, 100> uniquePtrs;
		//计时器开始
		Timer timer;
		for (int i = 0; i < uniquePtrs.size(); i++)
			uniquePtrs[i] = std::make_unique<vector2>();
	}

	std::cin.get();
}