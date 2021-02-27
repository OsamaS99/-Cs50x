WINDOW_WIDTH = 1280
WIDNOW_HEIGHT = 720

VIRTUAL_WIDTH = 432 
VIRTUAL_HEIGHT = 243





push = require 'push'
Class = require 'class'
require 'Paddle'
require 'Ball'
require 'Map'

startFont = love.graphics.newFont('font.ttf' , 32)
smallFont = love.graphics.newFont('font.ttf' , 8)
adFont = love.graphics.newFont('font.ttf' , 16)

sounds = {
          ['paddle_hit'] = love.audio.newSource('sounds/paddle_hit.wav', 'static'),
          ['score'] = love.audio.newSource('sounds/score.wav', 'static'),
          ['wall_hit'] = love.audio.newSource('sounds/wall_hit.wav', 'static')
      }


function love.load()
          love.window.setTitle('BreakOut')
          math.randomseed(os.time())
          love.graphics.setDefaultFilter('nearest', 'nearest')        
          push:setupScreen(VIRTUAL_WIDTH , VIRTUAL_HEIGHT , WINDOW_WIDTH , WIDNOW_HEIGHT , {
                    resizable = true
                    ,fullscreen = false ,
                    vsync = true
          })
          playState = 'start'
          hearts = 5
          score = 0
          paddle = Paddle()
          ball = Ball()
          map = Map(ball)
end
function love.resize(w, h)
          push:resize(w, h)
end


function love.update(dt)
          paddle:update(dt)
          if playState == 'reset' then
                    ball:reset()
          end
          if playState == 'victory' then 
                    score = 0
                    hearts = 5
                    ball:reset()
                    map:reset()
          end
          if playState == 'loss' then 
                    score = 0
                    hearts = 5
                    ball:reset()
                    map:reset()
          end
          if playState == 'start' then 
                    score = 0
                    hearts = 5
                    ball:reset()
                    map:reset()
          end
          if playState == 'play' then
                    ball:update(dt)
                    if ball:collide(paddle) then
                              ball.dy = -ball.dy 
                              ball.y = ball.y - 4  
                              if ball.dx < 0 then
                                        ball.dx = -math.random(80, 150)
                              else
                                        ball.dx = math.random(80, 150)
                              end
                              sounds['paddle_hit']:play()

                    elseif ball.x <= 0 then
                              ball.x = 0 
                              ball.dx = -ball.dx  
                              ball.dy = ball.dy * 1.05
                              sounds['wall_hit']:play()
                    elseif ball.x + ball.width >= VIRTUAL_WIDTH then
                              ball.x = VIRTUAL_WIDTH - ball.width 
                              ball.dx = -ball.dx 
                              ball.dy = ball.dy * 1.05
                              sounds['wall_hit']:play()

                    elseif ball.y <= 0 then
                              ball.y = 0 
                              ball.dy = - ball.dy 
                              sounds['wall_hit']:play()

                    elseif map:checkLower(ball) then
                              score = score +1 
                              ball.dy = -ball.dy
                              sounds['paddle_hit']:play()

                    elseif map:checkUpper(ball) then
                              score = score +1 
                              ball.dy = -ball.dy
                              sounds['paddle_hit']:play()

                    elseif map:checkRight(ball) then
                              score = score + 1 
                              ball.dx = -ball.dx
                              sounds['paddle_hit']:play()

                    elseif map:checkLeft(ball) then 
                              score = score + 1 
                              ball.dx = -ball.dx
                              sounds['paddle_hit']:play()
                    end
                    if score ==  map:getBrickHeight() * map:getBrickWidth() then
                              playState = 'victory'
                    end
                    if ball.y + ball.height >= VIRTUAL_HEIGHT and hearts > 1 then
                              playState = 'reset'
                              hearts = hearts - 1 
                              sounds['score']:play()

                    elseif  ball.y + ball.height >= VIRTUAL_HEIGHT and hearts == 1 then
                              playState = 'loss'
                              sounds['score']:play()

                    end
          end

end

function love.keypressed(key) 
          if key =='return' then
                    if playState == 'start' or playState == 'reset'  then
                              playState = 'play'
                    elseif playState == 'loss' then
                              playState = 'play'
                    elseif playState == 'victory' then 
                              playState = 'play'
                    end
          elseif key == 'escape' then
                    love.event.quit()
          end
end


function love.draw()
          push:apply('start')
          love.graphics.clear(40/255, 45/255, 52/255, 255/255)
          love.graphics.setDefaultFilter('nearest', 'nearest') 
          if playState == 'start' then
                    love.graphics.setFont(startFont)
                    love.graphics.printf('Welcome To Breakout!',0 , 20 , VIRTUAL_WIDTH , 'center')
                    love.graphics.setFont(adFont)
                    love.graphics.printf('Press Enter To Continue', 0 , VIRTUAL_HEIGHT / 2 , VIRTUAL_WIDTH , 'center')
                    paddle:render()
          elseif playState == 'play' then
                    paddle:render()
                    ball:render()
                    map:render()
                    love.graphics.setFont(smallFont)
                    love.graphics.setColor(0, 255, 0, 255)
                    love.graphics.printf('Score :'..tostring(score) ,0 , 5 , VIRTUAL_WIDTH , 'center')
                    love.graphics.print('Hearts :'..tostring(hearts) , VIRTUAL_WIDTH - 50 , 5)
                    love.graphics.setColor(1 , 1 , 1 , 1)
          elseif playState == 'reset' then
                    paddle:render()
                    ball:render()
                    map:render()
                    love.graphics.setFont(smallFont)
                    love.graphics.setColor(0, 255, 0, 255)
                    love.graphics.printf('Score :'..tostring(score) ,0 , 5 , VIRTUAL_WIDTH , 'center')
                    love.graphics.print('Hearts :'..tostring(hearts) , VIRTUAL_WIDTH - 50 , 5)
                    love.graphics.setColor(1 , 1 , 1 , 1)
                    love.graphics.setFont(adFont)
                    love.graphics.printf('Press Enter To Play' , 0 , VIRTUAL_HEIGHT / 2 + 15 , VIRTUAL_WIDTH , 'center')
                    
          elseif playState == 'loss' then
                    love.graphics.setFont(startFont)
                    love.graphics.printf('You Lost!',0 , 20 , VIRTUAL_WIDTH , 'center')
                    love.graphics.setFont(adFont)
                    love .graphics.printf('Your Total Score Is :'..tostring(score) , 0 , VIRTUAL_HEIGHT/2 , VIRTUAL_WIDTH , 'center')
                    love.graphics.printf('Press Enter To Play', 0 , VIRTUAL_HEIGHT / 2 + 20 , VIRTUAL_WIDTH , 'center')
                    paddle:render()
          elseif playState == 'victory' then
                    love.graphics.setFont(startFont)
                    love.graphics.printf('You Won!',0 , 20 , VIRTUAL_WIDTH , 'center')
                    love.graphics.setFont(adFont)
                    love .graphics.printf('Your Total Score Is :'..tostring(score) , 0 , VIRTUAL_HEIGHT/2 , VIRTUAL_WIDTH , 'center')
                    love.graphics.printf('Press Enter To Play', 0 , VIRTUAL_HEIGHT / 2 + 20 , VIRTUAL_WIDTH , 'center')
                    paddle:render()
          end

          displayFPS()
          push:apply('end')

end



function displayFPS()
          love.graphics.setFont(smallFont)
          love.graphics.setColor(0, 255, 0, 255)
          love.graphics.print('FPS: ' .. tostring(love.timer.getFPS()), 10, 5)
          love.graphics.setColor(1 , 1 , 1 , 1)
end

