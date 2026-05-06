-- auto_coverage.lua
-- Drives AUTO mode edge cases for LCOV coverage

local MAV_MODE_AUTO = 3
local MAV_CMD = {
    TAKEOFF = 22,
    WAYPOINT = 16,
    LAND = 21,
    RTL = 20,
    LOITER_TIME = 19,
    DO_CHANGE_SPEED = 178,
    CONDITION_YAW = 115
}

local stage = 0
local last_ms = 0

function send_mission()
    mission:clear()
    
    -- TAKEOFF
    mission:add_nav_cmd(MAV_CMD.TAKEOFF, 0, 0, 0, 0, 0, 10)

    -- WAYPOINT
    mission:add_nav_cmd(MAV_CMD.WAYPOINT, 0, 0, 0, 0, 0.0001, 0.0001, 10)

    -- CONDITION YAW
    mission:add_do_cmd(MAV_CMD.CONDITION_YAW, 90, 10, 1, 0)

    -- CHANGE SPEED
    mission:add_do_cmd(MAV_CMD.DO_CHANGE_SPEED, 1, 5, 0, 0)

    -- LOITER TIME
    mission:add_nav_cmd(MAV_CMD.LOITER_TIME, 3, 0, 0, 0, 0, 10)

    -- RTL
    mission:add_nav_cmd(MAV_CMD.RTL)

    mission:upload()
    gcs:send_text(6, "Mission uploaded")
end

function update()
    local now = millis()

    if stage == 0 then
        send_mission()
        stage = 1
    elseif stage == 1 and vehicle:get_mode() ~= MAV_MODE_AUTO then
        vehicle:set_mode(MAV_MODE_AUTO)
        stage = 2
    end

    return update, 1000
end

return update()
