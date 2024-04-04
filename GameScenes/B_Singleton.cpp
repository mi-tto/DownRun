#include <stddef.h>
#include "B_Singleton.h"

dataSingleton* dataSingleton::m_pInstance = NULL;

dataSingleton* dataSingleton::getInstance() {

	if (!m_pInstance)
	{
		m_pInstance = new dataSingleton;
	}

	return m_pInstance;
}

