#include <regex>
#include <sstream>
#include <Rendering/Shaders/ShaderReader.h>
#include <Logging/LoggerDefinition.h>


namespace ZEngine::Rendering::Shaders {

	ShaderReader::ShaderReader()
	{
	}

	ShaderReader::~ShaderReader() {
		if (m_filestream.is_open()) {
			m_filestream.close();
		}
	}

	ShaderOperationResult ShaderReader::Read(std::string_view filename) {
		std::regex reg{ m_regex_expression };

		m_filestream.open(filename.data(), std::ifstream::in);
		if (!m_filestream.is_open()) {
			Z_ENGINE_CORE_ERROR("====== Shader file : {} cannot be opened ======", filename.data());
			return ShaderOperationResult::FAILURE;
		}

		m_filestream.seekg(std::ifstream::beg);
		
		std::string current_line;

		while (std::getline(m_filestream, current_line)) {

			if (std::regex_match(current_line, reg)) {
				std::istringstream in(current_line);
				std::string type;
				in.seekg(std::string("#type ").size());
				in >> type;
				
				ShaderInformation shader_information{};
				shader_information.Name			= type;
				shader_information.Type			= (type == "vertex") ? ShaderType::VERTEX : ShaderType::FRAGMENT;
				shader_information.InternalType = (type == "vertex") ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;

				m_shader_info_collection.push_back(std::move(shader_information));
				in.clear();
				continue;
			}

			const auto last = std::prev(std::end(m_shader_info_collection));
			last->Source.append(current_line + "\n");
		}
		Z_ENGINE_CORE_INFO("====== Shader file : {} read succeeded ======", filename.data());
		m_filestream.close();
		return ShaderOperationResult::SUCCESS;
	}
	
	const std::vector<ShaderInformation>& ShaderReader::GetInformations() const {
		return m_shader_info_collection;
	}

	std::vector<ShaderInformation>& ShaderReader::GetInformations() {
		return m_shader_info_collection;
	}
}