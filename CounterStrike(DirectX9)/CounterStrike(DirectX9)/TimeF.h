#pragma once

#include "UtilConstant.h"

namespace UTILITY
{
	struct TimeClass
	{
	private :
		std::chrono::system_clock::time_point begin;
		std::chrono::system_clock::time_point end;
		std::chrono::duration<double> time;
		double accel;
		double realtime;
	public :
		_declspec(property(get = _GetDelta)) double Delta;
		_declspec(property(get = _GetRealTime)) double RealTime;
		_declspec(property(get = _GetAccel, put = _SetAccel)) double Accel;
		double _GetDelta() const { return accel * realtime; }
		double _GetRealTime() const { return realtime; }
		double _GetAccel() const { return accel; }
		void _SetAccel(double acc) { if (acc < 0) acc = 0; accel = acc; }
	public :
		void SetTimer()
		{
			end = std::chrono::system_clock::now();
			time = end - begin;
			begin = end;
			realtime = time.count();
		}
		TimeClass()
			:begin(std::chrono::system_clock::now())
			, end(std::chrono::system_clock::now())
			, accel(1), realtime(0)
		{}
	};

	extern TimeClass TIME;

	struct Invoke
	{
	protected:
		double DelayTime;
		std::function<void()> Func;
		virtual void FuncCall() { Func(); }
	public:
		void SetFunc(std::function<void()> _func) { Func = _func; }
		bool operator()()
		{
			if (DelayTime <= 0)
			{
				FuncCall();
				return true;
			}
			DelayTime = DelayTime - TIME.Delta;
			return false;
		}
	public:
		Invoke(double _delay, std::function<void()> _func)
			: DelayTime(_delay), Func(_func)
		{}
	};

	struct InvokeRepeat : public Invoke
	{
	private:
		double Repeat;
		double RepeatTime;
		virtual void FuncCall()
		{
			if (RepeatTime <= 0)
			{
				Func();
				RepeatTime += Repeat;
			}
			RepeatTime = RepeatTime - TIME.Delta;
		}
	public:
		bool operator()()
		{
			return Invoke::operator()();
		}
	public:
		InvokeRepeat(double _delay, std::function<void()> _func, double _repeat)
			: Invoke(_delay, _func), Repeat(_repeat), RepeatTime(0)
		{}
	};

	struct InvokeEvent : public Invoke
	{
	private:
		std::function<bool()> Event;
		virtual void FuncCall()
		{
			if (Event())
				Func();
		}
	public:
		bool operator()()
		{
			return Invoke::operator()();
		}
	public:
		InvokeEvent(std::function<void()> _func, std::function<bool()> _event)
			: Invoke(0, _func), Event(_event)
		{}
	};
}