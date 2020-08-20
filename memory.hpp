#pragma once

namespace memory
{
	template<typename type>
	bool write(HANDLE process_handle, std::uintptr_t address, const type& buffer)
	{
		return WriteProcessMemory(process_handle, reinterpret_cast<LPVOID>(address), reinterpret_cast<LPCVOID>(&buffer), sizeof(buffer), 0);
	}

	template<typename type>
	type read(HANDLE process_handle, std::uintptr_t address)
	{
		type buffer{};

		ReadProcessMemory(process_handle, reinterpret_cast<LPCVOID>(address), &buffer, sizeof(type), 0);

		return buffer;
	}

	std::uint32_t find_process_id(std::string process_name);
	std::uintptr_t get_module_base(std::uint32_t process_id, std::string module_name);
	std::uintptr_t signature_scan(std::uintptr_t module_start, std::uintptr_t module_size, const char* signature);
	std::uintptr_t resolve_remote_mov_instruction(HANDLE process_handle, std::uintptr_t module_base, std::uintptr_t address);
}

