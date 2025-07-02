#include "notifier.h"

uintptr_t PropertyNotifier::add_notification(PropertyNotification&& pn)
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

void PropertyNotifier::fire(PropertyID id) 
{
	for (auto& fn : m_vec_nf) {
		if (fn != nullptr)
			fn(id);
	}
}

void PropertyNotifier::clear_notifications() noexcept {
	m_vec_nf.clear();
}

void PropertyNotifier::remove_notification(uintptr_t cookie) noexcept {
	assert(cookie > 0 && cookie <= m_vec_nf.size());
	m_vec_nf[cookie - 1] = nullptr;
}