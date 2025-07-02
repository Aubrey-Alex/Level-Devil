#ifndef __FRAME_H__
#define __FRAME_H__

#include <functional>
#include <vector>
#include <memory>
#include <cassert>
#include "property_ids.h"

// 将 PropertyID 视为枚举类型，直接用于 std::function
using PropertyNotification = std::function<void(PropertyID)>;

// 基础的Observable类，用于实现属性变化通知
class PropertyTrigger {
public:
	PropertyTrigger() noexcept = default;
	PropertyTrigger(const PropertyTrigger&) = delete;
	~PropertyTrigger() noexcept = default;

	PropertyTrigger& operator=(const PropertyTrigger&) = delete;

	void clear_notifications() noexcept {
		m_vec_nf.clear();
	}

	uintptr_t add_notification(PropertyNotification&& pn);

	void remove_notification(uintptr_t cookie) noexcept {
		assert(cookie > 0 && cookie <= m_vec_nf.size());
		m_vec_nf[cookie - 1] = nullptr;
	}

protected:
    // MODIFIED: Change parameter type from uint32_t to PropertyID
	void fire(PropertyID id); // 注意：这里不再需要 PropertyTrigger::fire 这种写法

private:
	std::vector<PropertyNotification> m_vec_nf;
};

// MVVM基础接口
class IViewModel : public PropertyTrigger {
public:
	virtual ~IViewModel() = default;
	virtual void update(float deltaTime) = 0;
};

class IModel : public PropertyTrigger {
public:
	virtual ~IModel() = default;
	virtual int update(float deltaTime) = 0;
};

class IView {
public:
	virtual ~IView() = default;
};

#endif