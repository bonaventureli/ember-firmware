#include <float.h>
#include <math.h>

#include "canonical_machine.h"
#include "planner.h"
#include "util.h"
#include "MachineDefinitions.h"

cmSingleton_t cm;

void cm_init()
{
// You can assume all memory has been zeroed by a hard reset. If not, use this code:
//  memset(&cm, 0, sizeof(cm));   // reset canonicalMachineSingleton
//  memset(&gn, 0, sizeof(gn));   // clear all values, pointers and status
//  memset(&gf, 0, sizeof(gf));
//  memset(&gm, 0, sizeof(gm));

  // setup magic numbers
  cm.magic_start = MAGICNUM;
  cm.magic_end = MAGICNUM;
  /* JL: no gcode model
  gm.magic_start = MAGICNUM;
  gm.magic_end = MAGICNUM;

  // set gcode defaults
  cm_set_units_mode(cfg.units_mode);
  cm_set_coord_system(cfg.coord_system);
  cm_select_plane(cfg.select_plane);
  cm_set_path_control(cfg.path_control);
  cm_set_distance_mode(cfg.distance_mode);

  // never start a machine in a motion mode 
  gm.motion_mode = MOTION_MODE_CANCEL_MOTION_MODE;
  */

  // reset request flags
  //cm.feedhold_requested = false;
  //cm.queue_flush_requested = false;
  //cm.cycle_start_requested = false;

  // signal that the machine is ready for action
  //cm.machine_state = MACHINE_READY; 
  //cm.combined_state = COMBINED_READY;
}

void cm_cycle_start()
{
  //cm.machine_state = MACHINE_CYCLE;
  if (cm.cycle_state == CYCLE_OFF) {
    cm.cycle_state = CYCLE_MACHINING;     // don't change homing, probe or other cycles
    // JL: disable reporting rpt_clear_queue_report();         // clear queue reporting buffer counts
    // JL: motors are enabled in main st_enable_motors();             // enable motors if not already enabled
  }
}

/*
 * Program and cycle state functions
 *
 * cm_cycle_start()
 * cm_cycle_end()
 * cm_program_stop()      - M0
 * cm_optional_program_stop() - M1  
 * cm_program_end()       - M2, M30
 * _program_finalize()      - helper
 */
void cm_cycle_end() 
{
  if (cm.cycle_state == CYCLE_MACHINING) {
      //cm.machine_state = machine_state;
      cm.motion_state = MOTION_STOP;
      cm.cycle_state = CYCLE_OFF;         // don't end cycle if homing, probing, etc.
      cm.hold_state = FEEDHOLD_OFF;         // end feedhold (if in feed hold)
      //cm.cycle_start_requested = false;       //...and cancel any cycle start request

      mp_zero_segment_velocity();           // for reporting purposes
  }

  // execute program END resets
  /* JL: no gcode related state to update
  if (machine_state == MACHINE_PROGRAM_END) {
    cm_reset_origin_offsets();          // G92.1
  //  cm_suspend_origin_offsets();        // G92.2 - as per Kramer
    cm_set_coord_system(cfg.coord_system);    // reset to default coordinate system
    cm_select_plane(cfg.select_plane);      // reset to default arc plane
    cm_set_distance_mode(cfg.distance_mode);
    cm_set_units_mode(cfg.units_mode);      // reset to default units mode
    cm_spindle_control(SPINDLE_OFF);      // M5
    cm_flood_coolant_control(false);      // M9
    cm_set_inverse_feed_rate_mode(false);
  //  cm_set_motion_mode(MOTION_MODE_STRAIGHT_FEED);  // NIST specifies G1
    cm_set_motion_mode(MOTION_MODE_CANCEL_MOTION_MODE); 
  }
  */

  //JL: no reporting rpt_request_status_report(SR_IMMEDIATE_REQUEST);// request a final status report (not unfiltered)
  //JL: no config cmd_persist_offsets(cm.g10_persist_flag);   // persist offsets if any changes made
}

// JL: add this function for beginning feedhold
void cm_begin_feedhold(void)
{
    cm.motion_state = MOTION_HOLD;
    cm.hold_state = FEEDHOLD_SYNC;  // invokes hold from aline execution
}

void cm_end_feedhold(void)
{
    cm.hold_state = FEEDHOLD_END_HOLD;
    mp_end_hold();
}

void cm_straight_feed(uint8_t axisIndex, float distance, const AxisSettings& settings)
{
    float distances[AXES_COUNT] = { 0 };
    uint8_t directions[AXES_COUNT];

    distances[axisIndex] = distance;
    
    // Handle movement direction with a separate flag
    directions[Z_AXIS] = distances[Z_AXIS] < 0 ? 1 : 0;
    directions[R_AXIS] = distances[R_AXIS] < 0 ? 1 : 0;

    // The motion planning system does not properly deal with negative distances
    distances[axisIndex] = fabs(distances[axisIndex]);
    
    mp_aline(distances, directions, settings.Speed(), settings.MaxJerk());
}

// get parameter from cm struct
uint8_t cm_get_cycle_state() { return cm.cycle_state;}
uint8_t cm_get_motion_state() { return cm.motion_state;}
uint8_t cm_get_hold_state() { return cm.hold_state;}