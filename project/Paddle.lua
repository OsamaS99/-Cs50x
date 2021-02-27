Paddle = Class{}
PADDLE_SPEED = 200

function Paddle:init() 
          self.x  = VIRTUAL_WIDTH / 2 - 15
          self.y = VIRTUAL_HEIGHT - 15
          self.dx = 0
          self.height = 5
          self.width = 30
end


function Paddle:update(dt)
          if love.keyboard.isDown('right') then
                    self.dx = PADDLE_SPEED * dt 
          elseif love.keyboard.isDown('left') then
                    self.dx = -PADDLE_SPEED *dt
          else
                    self.dx = 0
          end

          if self.dx > 0 then
                    self.x = math.min(VIRTUAL_WIDTH - self.width , self.dx + self.x )
          elseif self.dx < 0 then 
                    self.x = math.max(0 , self.dx + self.x )
          end



end

function Paddle:render(dt)
          love.graphics.rectangle('fill' , self.x , self.y , self.width , self.height)
end
