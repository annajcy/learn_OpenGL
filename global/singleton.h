#pragma once

template<typename T>
class Singleton {
public:
	static T *get_instance() {
		if (m_instance == nullptr) {
			m_instance = new T();
		}
		return m_instance;
	}
	virtual ~Singleton() = default;
private:
	static T* m_instance;
	Singleton() = default;
};

template<typename T>
T* Singleton<T>::m_instance = nullptr;







