#pragma once

#include <GL/glew.h>

#include "Core/Base.h"

namespace Bit {

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	enum class BufferType
	{
		Stream_Draw = 0, Stream_Read, Stream_Copy, Static_Draw, Static_Read, Static_Copy, Dynamic_Draw, Dynamic_Read, Dynamic_Copy
	};

	static GLenum BufferTypeToGL(BufferType type)
	{
		switch (type)
		{
		case BufferType::Stream_Draw:  return GL_STREAM_DRAW;
		case BufferType::Stream_Read:  return GL_STREAM_READ;
		case BufferType::Stream_Copy:  return GL_STREAM_COPY;
		case BufferType::Static_Draw:  return GL_STATIC_DRAW;
		case BufferType::Static_Read:  return GL_STATIC_READ;
		case BufferType::Static_Copy:  return GL_STATIC_COPY;
		case BufferType::Dynamic_Draw: return GL_DYNAMIC_DRAW;
		case BufferType::Dynamic_Read: return GL_DYNAMIC_READ;
		case BufferType::Dynamic_Copy: return GL_DYNAMIC_COPY;
		}

		BIT_CORE_ASSERT(false, "Unknown Vertex Buffer Type!");
		return 0;
	}

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Bool:     return 1;
		}

		BIT_CORE_ASSERT(false, "Unknown Shader Data Type!");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Float:   return 1;
				case ShaderDataType::Float2:  return 2;
				case ShaderDataType::Float3:  return 3;
				case ShaderDataType::Float4:  return 4;
				case ShaderDataType::Mat3:    return 3 * 3;
				case ShaderDataType::Mat4:    return 4 * 4;
				case ShaderDataType::Int:     return 1;
				case ShaderDataType::Int2:    return 2;
				case ShaderDataType::Int3:    return 3;
				case ShaderDataType::Int4:    return 4;
				case ShaderDataType::Bool:    return 1;
			}

			BIT_CORE_ASSERT(false, "Unknown Shader Data Type!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		VertexBuffer(float* vertices, uint32_t size, const BufferType& type = BufferType::Static_Draw);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

		const BufferLayout& GetLayout() const { return m_Layout; }
		void SetLayout(const BufferLayout& layout) { m_Layout = layout; }
		
		void SetData(const uint32_t& offset, const void* vertices, const uint32_t& size);

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	class IndexBuffer
	{
	public:
		IndexBuffer(uint32_t* indices, uint32_t size, const BufferType& type = BufferType::Static_Draw);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		void SetData(const uint32_t& offset, const void* vertices, const uint32_t& size);

		uint32_t GetCount() const { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

}