#pragma once

#include "AbstractDialogModel.h"

namespace fso {
namespace fred {
namespace dialogs {

class ShipFlagsDialogModel : public AbstractDialogModel {
  private:
	void initializeData();

	template <typename T>
	void modify(T& a, const T& b);

	bool _modified = false;

	int m_red_alert_carry;
	int m_scannable;
	int m_reinforcement;
	int m_protect_ship;
	int m_beam_protect_ship;
	int m_flak_protect_ship;
	int m_laser_protect_ship;
	int m_missile_protect_ship;
	int m_no_dynamic;
	int m_no_arrival_music;
	int m_kamikaze;
	int m_invulnerable;
	int m_targetable_as_bomb;
	int m_immobile;
	int m_ignore_count;
	int m_hidden;
	int m_primitive_sensors;
	int m_no_subspace_drive;
	int m_affected_by_gravity;
	int m_toggle_subsystem_scanning;
	int m_escort;
	int m_destroy;
	int m_cargo_known;
	int m_special_warpin;
	int m_disable_messages;
	int m_no_death_scream;
	int m_always_death_scream;
	int m_guardian;
	int m_vaporize;
	int m_stealth;
	int m_friendly_stealth_invisible;
	int m_nav_carry;
	int m_nav_needslink;
	int m_hide_ship_name;
	int m_disable_ets;
	int m_cloaked;
	int m_set_class_dynamically;
	int m_scramble_messages;
	int m_no_collide;
	int m_no_disabled_self_destruct;

	int m_kdamage;
	int m_destroy_value;
	int m_escort_value;
	int m_respawn_priority;

	void set_modified();
	int tristate_set(int val, int cur_state);

  public:
	ShipFlagsDialogModel(QObject* parent, EditorViewport* viewport);

	bool apply() override;
	void reject() override;

	void setDestroyed(bool);
	bool getDestroyed();

	bool query_modified();
};

template <typename T>
inline void ShipFlagsDialogModel::modify(T& a, const T& b)
{
	if (a != b) {
		a = b;
		set_modified();
		modelChanged();
	}
}
} // namespace dialogs
} // namespace fred
} // namespace fso