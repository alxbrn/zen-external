#pragma once
#include <cstdint>
#include <string>
#include <vector>

struct _LDR_DATA_TABLE_ENTRY;
struct _IMAGE_NT_HEADERS;

namespace remote
{
	class process_t;

	class module_t
	{
	public:
		module_t();
		module_t(process_t* process, _LDR_DATA_TABLE_ENTRY* entry);
		~module_t();

		bool refresh();
		bool is_valid() const;

		operator bool() const;
		bool operator==(const module_t& rhs) const;
		const std::string& name() const;

		uintptr_t get_proc_address(const char* export_name);
		uintptr_t find_pattern(const char* pattern);
	private:
		bool load_nt_headers();
		bool load_exports();

		process_t* process_;
		uintptr_t base_;
		size_t size_;
		std::string name_;
		std::string module_path_;
		uint8_t* module_bytes_;
		_IMAGE_NT_HEADERS* nt_headers_;

		std::vector<std::pair<std::string, uintptr_t>> exports_;
	};
} // namespace remote
