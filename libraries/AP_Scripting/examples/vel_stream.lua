function update()
    if vehicle:get_mode() == vehicle.MODE_AVOID_ADSB then
        vehicle:set_velocity_NED(1.0, 0.0, 0.0)
    end
    return update, 100
end

return update()
