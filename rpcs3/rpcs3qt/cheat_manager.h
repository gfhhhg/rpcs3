#pragma once

#include "util/types.hpp"

#include <QDialog>
#include <QTableWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTimer>

#include <string>
#include <vector>
#include <map>

#include "Utilities/cheat_info.h"

class cheat_engine
{
public:
	cheat_engine();

	bool exist(const std::string& game, const u32 offset) const;
	void add(const std::string& game, const std::string& description, const cheat_type type, const u32 offset, const std::string& red_script);
	cheat_info* get(const std::string& game, const u32 offset);
	bool erase(const std::string& game, const u32 offset);

	bool import_cheats_from_str(std::string_view str_cheats);
	std::string export_cheats_to_str() const;
	void save() const;

	// Static functions to find/get/set values in ps3 memory
	static bool resolve_script(u32& final_offset, const u32 offset, std::string_view red_script);

	template <typename T>
	static std::vector<u32> search(const T value, const std::vector<u32>& to_filter,
		search_compare_mode mode = search_compare_mode::equal, const T value2 = {},
		const std::map<u32, T>* prev_values = nullptr,
		u32 mem_start = 0x00010000, u32 mem_end = 0xC0000000);

	template <typename T>
	static std::vector<std::pair<u32, T>> scan_all_memory(u32 max_entries = 5000000, bool use_chunked_scan = true,
		u32 mem_start = 0x00010000, u32 mem_end = 0xC0000000);

	template <typename T>
	static T get_value(const u32 offset, bool& success);
	template <typename T>
	static bool set_value(const u32 offset, const T value);

	static bool is_addr_safe(const u32 offset);
	static u32 reverse_lookup(const u32 addr, const u32 max_offset, const u32 max_depth, const u32 cur_depth = 0);

	std::map<std::string, std::map<u32, cheat_info>> cheats;

private:
	const std::string m_cheats_filename = "cheats.yml";
};

class cheat_manager_dialog : public QDialog
{
	Q_OBJECT
public:
	cheat_manager_dialog(QWidget* parent = nullptr);
	~cheat_manager_dialog();
	static cheat_manager_dialog* get_dlg(QWidget* parent = nullptr);

	cheat_manager_dialog(cheat_manager_dialog const&) = delete;
	void operator=(cheat_manager_dialog const&) = delete;

protected:
	void update_cheat_list();
	void do_the_search();

	template <typename T>
	T convert_from_QString(const QString& str, bool& success);

	template <typename T>
	bool convert_and_search();
	template <typename T>
	std::pair<bool, bool> convert_and_set(u32 offset);

protected:
	QTableWidget* tbl_cheats = nullptr;
	QListWidget* lst_search = nullptr;

	QLineEdit* edt_value_final = nullptr;
	QPushButton* btn_apply = nullptr;

	QLineEdit* edt_cheat_search_value = nullptr;
	QLineEdit* edt_cheat_search_value2 = nullptr;
	QComboBox* cbx_cheat_search_type = nullptr;
	QComboBox* cbx_compare_mode = nullptr;
	QComboBox* cbx_memory_range = nullptr;
	QLineEdit* edt_mem_start = nullptr;
	QLineEdit* edt_mem_end = nullptr;

	QPushButton* btn_new_search = nullptr;
	QPushButton* btn_filter_results = nullptr;

	u32 current_offset{};
	std::vector<u32> offsets_found;
	std::vector<std::pair<u32, u64>> last_search_values;

	QTimer* m_lock_timer = nullptr;

	cheat_engine g_cheat;

private:
	static cheat_manager_dialog* inst;

	void update_search_button_states();
	void update_locked_values();

	QString get_localized_cheat_type(cheat_type type);
	QString get_localized_compare_mode(search_compare_mode mode);
};
