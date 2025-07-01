#include "frame.h"

uintptr_t PropertyTrigger::add_notification(PropertyNotification&& pn)
{
	uintptr_t index = 0;
	for (auto& fn : m_vec_nf) {
		if (fn == nullptr) {
			fn = std::move(pn);
			return index + 1;
		}
		index ++;
	}
	m_vec_nf.push_back(std::move(pn));
	return index + 1;
}

// MODIFIED: Change parameter type from uint32_t to PropertyID
void PropertyTrigger::fire(PropertyID id) // 这里同样去掉 PropertyTrigger::fire 这种写法
{
	for (auto& fn : m_vec_nf) {
		if (fn != nullptr)
			fn(id);
	}
}