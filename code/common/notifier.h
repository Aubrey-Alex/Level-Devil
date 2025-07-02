#ifndef __notifier_H__
#define __notifier_H__

#include <functional>
#include <vector>
#include <memory>
#include <cassert>
#include "property_ids.h"

// 将 PropertyID 视为枚举类型，直接用于 std::function
using PropertyNotification = std::function<void(PropertyID)>;

// 基础的Observable类，用于实现属性变化通知
class PropertyNotifier {
public:
	PropertyNotifier() noexcept = default;
	PropertyNotifier(const PropertyNotifier&) = delete;
	~PropertyNotifier() noexcept = default;

	PropertyNotifier& operator=(const PropertyNotifier&) = delete;

	void clear_notifications() noexcept;

	uintptr_t add_notification(PropertyNotification&& pn);

	void remove_notification(uintptr_t cookie) noexcept;

protected:
	void fire(PropertyID id);

private:
	std::vector<PropertyNotification> m_vec_nf;
};

#endif