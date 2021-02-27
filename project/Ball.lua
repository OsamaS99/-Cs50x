Ball = Class{}

function Ball:init()
          self.height = 6
          self.width = 6 
          self.x = VIRTUAL_WIDTH / 2 - 3 
          self.y= VIRTUAL_HEIGHT /2 -3
          self.dx  =  math.random(2) == 1 and -100 or 100 
          self.dy = math.random(80, 100)
          
end



function Ball:update(dt) 
          self.x = self.x + self.dx  * dt
          self.y = self.y + self.dy * dt 

end


function Ball:reset() 
          self.x = VIRTUAL_WIDTH / 2 - 3 
          self.y= VIRTUAL_HEIGHT /2 -3
          self.dx  =  math.random(2) == 1 and -100 or 100 
          self.dy = math.random(80, 100)
end


function Ball:collide(paddle)
          if self.y  + self.height < paddle.y or self.x+ self.width <  paddle.x or self.x > paddle.x + paddle.width then 
                    return false
          end
          return true
end



function Ball:render() 

          love.graphics.rectangle('fill' , self.x , self.y , self.width , self.height)
end
