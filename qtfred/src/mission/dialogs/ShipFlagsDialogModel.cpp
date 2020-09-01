//
//

#include "ShipFlagsDialogModel.h"

#include "ui/dialogs/ShipFlagsDialog.h"

#include <globalincs/linklist.h>

#include <QtWidgets>

namespace fso {
namespace fred {
namespace dialogs {
int ShipFlagsDialogModel::tristate_set(int val, int cur_state)
{
	if (val) {
		if (!cur_state) {
			return 1;
		}
	} else {
		if (cur_state) {
			return 1;
		}
	}
	if (cur_state == 1) {

		return 2;
	} else {
		return 0;
	}
}
ShipFlagsDialogModel::ShipFlagsDialogModel(QObject* parent, EditorViewport* viewport)
	: AbstractDialogModel(parent, viewport)
{
	initializeData();
}

void ShipFlagsDialogModel::initializeData()
{
	object* objp;
	ship* shipp;
	bool ship_in_wing = false;
	int j, first;

	first = 1;

	objp = GET_FIRST(&obj_used_list);
	while (objp != END_OF_LIST(&obj_used_list)) {
		if ((objp->type == OBJ_START) || (objp->type == OBJ_SHIP)) {
			if (objp->flags[Object::Object_Flags::Marked]) {
				shipp = &Ships[objp->instance];

				if (first) {
					first = 0;
					m_scannable = (shipp->flags[Ship::Ship_Flags::Scannable]) ? 2 : 0;
					m_red_alert_carry = (shipp->flags[Ship::Ship_Flags::Red_alert_store_status]) ? 2 : 0;
					m_special_warpin = (objp->flags[Object::Object_Flags::Special_warpin]) ? 2 : 0;
					m_protect_ship = (objp->flags[Object::Object_Flags::Protected]) ? 2 : 0;
					m_beam_protect_ship = (objp->flags[Object::Object_Flags::Beam_protected]) ? 2 : 0;
					m_flak_protect_ship = (objp->flags[Object::Object_Flags::Flak_protected]) ? 2 : 0;
					m_laser_protect_ship = (objp->flags[Object::Object_Flags::Laser_protected]) ? 2 : 0;
					m_missile_protect_ship = (objp->flags[Object::Object_Flags::Missile_protected]) ? 2 : 0;
					m_invulnerable = (objp->flags[Object::Object_Flags::Invulnerable]) ? 2 : 0;
					m_targetable_as_bomb = (objp->flags[Object::Object_Flags::Targetable_as_bomb]) ? 2 : 0;
					m_immobile = (objp->flags[Object::Object_Flags::Immobile]) ? 2 : 0;
					m_hidden = (shipp->flags[Ship::Ship_Flags::Hidden_from_sensors]) ? 2 : 0;
					m_primitive_sensors = (shipp->flags[Ship::Ship_Flags::Primitive_sensors]) ? 2 : 0;
					m_no_subspace_drive = (shipp->flags[Ship::Ship_Flags::No_subspace_drive]) ? 2 : 0;
					m_affected_by_gravity = (shipp->flags[Ship::Ship_Flags::Affected_by_gravity]) ? 2 : 0;
					m_toggle_subsystem_scanning = (shipp->flags[Ship::Ship_Flags::Toggle_subsystem_scanning]) ? 2 : 0;
					m_ignore_count = (shipp->flags[Ship::Ship_Flags::Ignore_count]) ? 2 : 0;
					m_no_arrival_music = (shipp->flags[Ship::Ship_Flags::No_arrival_music]) ? 2 : 0;
					m_cargo_known = (shipp->flags[Ship::Ship_Flags::Cargo_revealed]) ? 2 : 0;
					m_no_dynamic = (Ai_info[shipp->ai_index].ai_flags[AI::AI_Flags::No_dynamic]) ? 2 : 0;
					m_disable_messages = (shipp->flags[Ship::Ship_Flags::No_builtin_messages]) ? 2 : 0;
					m_set_class_dynamically = (shipp->flags[Ship::Ship_Flags::Set_class_dynamically]) ? 2 : 0;
					m_no_death_scream = (shipp->flags[Ship::Ship_Flags::No_death_scream]) ? 2 : 0;
					m_always_death_scream = (shipp->flags[Ship::Ship_Flags::Always_death_scream]) ? 2 : 0;
					m_guardian = (shipp->ship_guardian_threshold) ? 2 : 0;
					m_vaporize = (shipp->flags[Ship::Ship_Flags::Vaporize]) ? 2 : 0;
					m_stealth = (shipp->flags[Ship::Ship_Flags::Stealth]) ? 2 : 0;
					m_friendly_stealth_invisible = (shipp->flags[Ship::Ship_Flags::Friendly_stealth_invis]) ? 2 : 0;
					m_nav_carry = (shipp->flags[Ship::Ship_Flags::Navpoint_carry]) ? 2 : 0;
					m_nav_needslink = (shipp->flags[Ship::Ship_Flags::Navpoint_needslink]) ? 2 : 0;
					m_hide_ship_name = (shipp->flags[Ship::Ship_Flags::Hide_ship_name]) ? 2 : 0;
					m_disable_ets = (shipp->flags[Ship::Ship_Flags::No_ets]) ? 2 : 0;
					m_cloaked = (shipp->flags[Ship::Ship_Flags::Cloaked]) ? 2 : 0;
					m_scramble_messages = (shipp->flags[Ship::Ship_Flags::Scramble_messages]) ? 2 : 0;
					m_no_collide = (objp->flags[Object::Object_Flags::Collides]) ? 0 : 2;
					m_no_disabled_self_destruct = (shipp->flags[Ship::Ship_Flags::No_disabled_self_destruct]) ? 2 : 0;

					m_destroy = (shipp->flags[Ship::Ship_Flags::Kill_before_mission]) ? 2 : 0;
					m_destroy_value = shipp->final_death_time;

					m_kamikaze = (Ai_info[shipp->ai_index].ai_flags[AI::AI_Flags::Kamikaze]) ? 2 : 0;
					m_kdamage = Ai_info[shipp->ai_index].kamikaze_damage;

					m_escort = (shipp->flags[Ship::Ship_Flags::Escort]) ? 2 : 0;
					m_escort_value = shipp->escort_priority;

					if (The_mission.game_type & MISSION_TYPE_MULTI) {
						m_respawn_priority = shipp->respawn_priority;
					}

					for (j = 0; j < Num_reinforcements; j++) {
						if (!stricmp(Reinforcements[j].name, shipp->ship_name)) {
							break;
						}
					}

					m_reinforcement = (j < Num_reinforcements) ? 1 : 0;

					// check if ship in wing
					ship_in_wing = (shipp->wingnum != -1);
					;
				} else {

					m_scannable = tristate_set(shipp->flags[Ship::Ship_Flags::Scannable], m_scannable);
					m_red_alert_carry =
						tristate_set(shipp->flags[Ship::Ship_Flags::Red_alert_store_status], m_red_alert_carry);
					m_special_warpin =
						tristate_set(objp->flags[Object::Object_Flags::Special_warpin], m_special_warpin);
					m_protect_ship = tristate_set(objp->flags[Object::Object_Flags::Protected], m_protect_ship);
					m_beam_protect_ship =
						tristate_set(objp->flags[Object::Object_Flags::Beam_protected], m_beam_protect_ship);
					m_flak_protect_ship =
						tristate_set(objp->flags[Object::Object_Flags::Flak_protected], m_flak_protect_ship);
					m_laser_protect_ship =
						tristate_set(objp->flags[Object::Object_Flags::Laser_protected], m_laser_protect_ship);
					m_missile_protect_ship =
						tristate_set(objp->flags[Object::Object_Flags::Missile_protected], m_missile_protect_ship);
					m_invulnerable = tristate_set(objp->flags[Object::Object_Flags::Invulnerable], m_invulnerable);
					m_targetable_as_bomb =
						tristate_set(objp->flags[Object::Object_Flags::Targetable_as_bomb], m_targetable_as_bomb);
					m_immobile = tristate_set(objp->flags[Object::Object_Flags::Immobile], m_immobile);
					m_hidden = tristate_set(shipp->flags[Ship::Ship_Flags::Hidden_from_sensors], m_hidden);
					m_primitive_sensors =
						tristate_set(shipp->flags[Ship::Ship_Flags::Primitive_sensors], m_primitive_sensors);
					m_no_subspace_drive =
						tristate_set(shipp->flags[Ship::Ship_Flags::No_subspace_drive], m_no_subspace_drive);
					m_affected_by_gravity =
						tristate_set(shipp->flags[Ship::Ship_Flags::Affected_by_gravity], m_affected_by_gravity);
					m_toggle_subsystem_scanning =
						tristate_set(shipp->flags[Ship::Ship_Flags::Toggle_subsystem_scanning],
							m_toggle_subsystem_scanning);
					m_ignore_count = tristate_set(shipp->flags[Ship::Ship_Flags::Ignore_count], m_ignore_count);
					m_no_arrival_music =
						tristate_set(shipp->flags[Ship::Ship_Flags::No_arrival_music], m_no_arrival_music);
					m_cargo_known = tristate_set(shipp->flags[Ship::Ship_Flags::Cargo_revealed], m_cargo_known);
					m_no_dynamic =
						tristate_set(Ai_info[shipp->ai_index].ai_flags[AI::AI_Flags::No_dynamic], m_no_dynamic);
					m_disable_messages =
						tristate_set(shipp->flags[Ship::Ship_Flags::No_builtin_messages], m_disable_messages);
					m_set_class_dynamically =
						tristate_set(shipp->flags[Ship::Ship_Flags::Set_class_dynamically], m_set_class_dynamically);
					m_no_death_scream =
						tristate_set(shipp->flags[Ship::Ship_Flags::No_death_scream], m_no_death_scream);
					m_always_death_scream =
						tristate_set(shipp->flags[Ship::Ship_Flags::Always_death_scream], m_always_death_scream);
					m_guardian = tristate_set(shipp->ship_guardian_threshold, m_guardian);
					m_vaporize = tristate_set(shipp->flags[Ship::Ship_Flags::Vaporize], m_vaporize);
					m_stealth = tristate_set(shipp->flags[Ship::Ship_Flags::Stealth], m_stealth);
					m_friendly_stealth_invisible = tristate_set(shipp->flags[Ship::Ship_Flags::Friendly_stealth_invis],
						m_friendly_stealth_invisible);
					m_nav_carry = tristate_set(shipp->flags[Ship::Ship_Flags::Navpoint_carry], m_nav_carry);
					m_nav_needslink = tristate_set(shipp->flags[Ship::Ship_Flags::Navpoint_needslink], m_nav_needslink);
					m_hide_ship_name = tristate_set(shipp->flags[Ship::Ship_Flags::Hide_ship_name], m_hide_ship_name);
					m_disable_ets = tristate_set(shipp->flags[Ship::Ship_Flags::No_ets], m_disable_ets);
					m_cloaked = tristate_set(shipp->flags[Ship::Ship_Flags::Cloaked], m_cloaked);
					m_scramble_messages =
						tristate_set(shipp->flags[Ship::Ship_Flags::Scramble_messages], m_scramble_messages);
					m_no_collide = tristate_set(!(objp->flags[Object::Object_Flags::Collides]), m_no_collide);
					m_no_disabled_self_destruct =
						tristate_set(shipp->flags[Ship::Ship_Flags::No_disabled_self_destruct],
							m_no_disabled_self_destruct);

					// check the final death time and set the internal variable according to whether or not
					// the final_death_time is set.  Also, the value in the edit box must be set if all the
					// values are the same, and cleared if the values are not the same.
					m_destroy = tristate_set(shipp->flags[Ship::Ship_Flags::Kill_before_mission], m_destroy);
					m_destroy_value = shipp->final_death_time;

					m_kamikaze = tristate_set(Ai_info[shipp->ai_index].ai_flags[AI::AI_Flags::Kamikaze], m_kamikaze);
					m_kdamage = Ai_info[shipp->ai_index].kamikaze_damage;

					m_escort = tristate_set(shipp->flags[Ship::Ship_Flags::Escort], m_escort);
					m_escort_value = shipp->escort_priority;

					if (The_mission.game_type & MISSION_TYPE_MULTI) {
						m_respawn_priority = shipp->escort_priority;
					}

					for (j = 0; j < Num_reinforcements; j++) {
						if (!stricmp(Reinforcements[j].name, shipp->ship_name)) {
							break;
						}
					}
					m_reinforcement = tristate_set(j < Num_reinforcements, m_reinforcement);

					// check if ship in wing
					ship_in_wing = (shipp->wingnum != -1);
					;
				}
			}
		}

		objp = GET_NEXT(objp);
	}
}
} // namespace dialogs
} // namespace fred
} // namespace fso
