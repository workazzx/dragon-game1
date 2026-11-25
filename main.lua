math.randomseed(os.time())

local hp = 100
local potions = 2
local stamina = 3
local dhp = 150
local rage = false

local names = {"fire", "claw", "roar"}
local texts = {
  fire = "дракон набирает воздух",
  claw = "дракон пригнулся",
  roar = "дракон задрал голову"
}

while hp > 0 and dhp > 0 do
  print("")
  print("hp " .. hp .. " | зелья " .. potions .. " | сила " .. stamina .. " | дракон " .. dhp)

  local real = names[math.random(1, 3)]
  local shown = real
  if math.random(1, 100) <= 25 then
    shown = names[math.random(1, 3)]
  end
  print(texts[shown])
  print("1 удар, 2 блок, 3 перекат, 4 зелье, 5 отдых")
  io.write("> ")
  local c = io.read()
  if c == nil then break end

  local block, roll = false, false

  if c == "1" and stamina > 0 then
    local d = math.random(15, 25)
    stamina = stamina - 1
    dhp = dhp - d
    print("попал, -" .. d)
  elseif c == "2" then
    block = true
  elseif c == "3" then
    roll = true
  elseif c == "4" and potions > 0 then
    potions = potions - 1
    hp = math.min(100, hp + 35)
    print("выпил зелье")
  elseif c == "5" then
    stamina = math.min(3, stamina + 2)
    print("отдышался")
  else
    print("промазал")
  end

  if dhp > 0 then
    if not rage and dhp <= 75 then
      rage = true
      print("дракон разозлился")
    end

    local k = 1
    if rage then k = 1.4 end
    local dmg = 0

    if real == "fire" then
      dmg = 25 * k
      if block then dmg = dmg * 0.5 end
      if roll then dmg = dmg * 0.7 end
      print("дракон дунул огнём")
    elseif real == "claw" then
      dmg = 18 * k
      if block then dmg = dmg * 0.2 end
      if roll then dmg = 0 end
      print("дракон ударил лапой")
    else
      dmg = 8 * k
      if roll then dmg = 0 end
      if not block then
        stamina = math.max(0, stamina - 1)
        print("от рёва пропала сила")
      end
    end

    dmg = math.floor(dmg)
    hp = hp - dmg
    if dmg > 0 then print("тебе -" .. dmg) end
  end
end

if hp > 0 and dhp <= 0 then
  print("\nпобеда")
elseif hp <= 0 then
  print("\nты проиграл")
end
