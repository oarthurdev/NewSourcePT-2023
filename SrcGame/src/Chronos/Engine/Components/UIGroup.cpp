
#include "UIGroup.h"
#include "UI.h"
#include "UIElement.h"
#include <memory>

namespace UI
{
	Group::Group() : Element()
	{
	}

	Group::~Group()
	{
	}

	void Group::SetGroup(std::shared_ptr<Group> pGroupObj)
	{
		pGroup = pGroupObj;
	}
}


