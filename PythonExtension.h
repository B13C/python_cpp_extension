#pragma once
// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� PYTHONEXTENSION_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ���Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// PYTHONEXTENSION_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef PYTHONEXTENSION_EXPORTS
#define PYTHONEXTENSION_API __declspec(dllexport)
#else
#define PYTHONEXTENSION_API __declspec(dllimport)
#endif
#include "pch.h"

// �����Ǵ� dll ������
class PYTHONEXTENSION_API CPythonExtension {
public:
	CPythonExtension(void);
	// TODO: �ڴ˴���ӷ�����
	string retStr();
};

extern PYTHONEXTENSION_API int nPythonExtension;

PYTHONEXTENSION_API int fnPythonExtension(void);