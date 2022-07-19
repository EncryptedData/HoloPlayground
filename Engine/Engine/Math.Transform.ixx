
module;

#include <glm/gtx/quaternion.hpp> // header doesn't play nicely as module ~July 2022

export module Engine.Math.Transform;
import <glm/glm.hpp>;


namespace Engine::Math
{
	export glm::mat4 AffineScale(const glm::vec3& scale);
	export glm::mat4 AffineScale(float scale);
	export glm::mat4 AffineRotation(const glm::quat& rotation);
	export glm::mat4 AffineTranslation(const glm::vec3& position);

	export class Transform
	{
	public:
		explicit Transform();

		Transform(glm::vec3 position, glm::vec3 scale, glm::quat rotation);

		void SetPosition(const glm::vec3& position);
		void SetScale(const glm::vec3& scale);
		void SetScale(float scale);
		void SetRotation(const glm::quat& rotation);

		const glm::vec3& GetPosition() const;
		const glm::vec3& GetScale() const;
		const glm::quat& GetRotation() const;

		const glm::mat4& GetTransform();

	private:
		glm::mat4 _transform;
		glm::vec3 _position;
		glm::vec3 _scale;
		glm::quat _rotation;
		bool _isDirty;

		void RecalculateTransform();
	};
}

module :private;

namespace Engine::Math
{
	Transform::Transform(glm::vec3 position, glm::vec3 scale, glm::quat rotation) :
		_transform{},
		_position{position},
		_scale{scale},
		_rotation{rotation},
		_isDirty{true}
	{
		RecalculateTransform();
	}

	void Transform::SetPosition(const glm::vec3& position)
	{
		_isDirty = true;
		_position = position;
	}

	void Transform::SetScale(const glm::vec3& scale)
	{
		_isDirty = true;
		_scale = scale;
	}

	void Transform::SetScale(float scale)
	{
		_isDirty = true;
		_scale.x = scale;
		_scale.y = scale;
		_scale.z = scale;
	}

	void Transform::SetRotation(const glm::quat& rotation)
	{
		_isDirty = true;
		_rotation = rotation;
	}

	const glm::vec3& Transform::GetPosition() const
	{
		return _position;
	}

	const glm::vec3& Transform::GetScale() const
	{
		return _scale;
	}

	const glm::quat& Transform::GetRotation() const
	{
		return _rotation;
	}

	const glm::mat4& Transform::GetTransform()
	{
		RecalculateTransform();
		return _transform;
	}

	void Transform::RecalculateTransform()
	{
		if (!_isDirty)
		{
			return;
		}

		_transform = AffineScale(_scale);
		_transform *= AffineRotation(_rotation);
		_transform *= AffineTranslation(_position);
		_isDirty = false;
	}

	glm::mat4 AffineScale(const glm::vec3& scale)
	{
		glm::mat4 m(1.0f);
		
		for (int i = 0; i < 3; i++)
		{
			m[i][i] = scale[i];
		}

		return m;
	}

	glm::mat4 AffineScale(float scale)
	{
		glm::mat4 m(scale);
		m[3][3] = 1.0f;

		return m;
	}

	glm::mat4 AffineRotation(const glm::quat& rotation)
	{
		return glm::toMat4(rotation);
	}

	glm::mat4 AffineTranslation(const glm::vec3& position)
	{
		glm::mat4 m(1.0f);

		for (int i = 0; i < 3; i++)
		{
			m[i][0] = position[i];
		}

		return m;
	}
}
