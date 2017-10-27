#include "..\\pch.h"
#include "Camera.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Camera::Camera(int width, int height)
	:m_eyepos(0,3.0f,4.0f)
	,m_refpos(0,0,0)
	,m_upvec(0,1.0f,0)
	,m_fovY(XMConvertToRadians(60.0f))
	,m_aspect((float)width / height)
	,m_nearClip(0.1f)
	,m_farClip(1000.0f)
{

}

Camera::~Camera()
{

}

void Camera::Update()
{
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);

	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);
}

Matrix Camera::GetViewMatrix()
{
	return m_view;
}

Matrix Camera::GetProjectionMatrix()
{
	return m_proj;
}

void Camera::Seteyepos(Vector3 eyepos)
{
	m_eyepos = eyepos;
}

void Camera::Setrefpos(Vector3 refpos)
{
	m_refpos = refpos;
}

void Camera::Setupvec(Vector3 upvec)
{
	m_upvec = upvec;
}

void Camera::SetfovY(float fovY)
{
	m_fovY = fovY;
}

void Camera::Setaspect(float aspect)
{
	m_aspect = aspect;
}

void Camera::SetnearClip(float nearClip)
{
	m_nearClip = nearClip;
}

void Camera::SetfarClip(float farClip)
{
	m_farClip = farClip;
}