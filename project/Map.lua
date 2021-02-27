Map = Class{}



function Map:init(ball) 
          self.brickHeight = 10
          self.brickWidth = 20 
          self.mapBirckWidth = math.floor(VIRTUAL_WIDTH  / self.brickWidth)
          self.mapBirckHeight = 5
          self.bricks = {}
          for y = 1 , self.mapBirckHeight do
                    for x = 1 , self.mapBirckWidth do
                              self:setTile(x, y , 1)
                    end
          end
end
function Map:getBrickHeight()
          return self.mapBirckHeight
end
function Map:getBrickWidth()
          return self.mapBirckWidth
end



function Map:setTile(x , y , type) 
          self.bricks[(y - 1) * self.mapBirckWidth + x] = type
end
function Map:getTile (x ,y ) 
          return self.bricks[(y - 1) * self.mapBirckWidth + x]
end

function Map:reset() 
          for y = 1 , self.mapBirckHeight do
                    for x = 1 , self.mapBirckWidth do
                              self:setTile(x, y , 1)
                    end
          end
end

function Map:checkLower(ball) 
          for y = 1, self.mapBirckHeight do
                    for x = 1, self.mapBirckWidth do
                              local Yaxis = (y-1) * self.brickHeight  + self.brickHeight * 2
                              local Xaxis =  5 +  (x - 1) * self.brickWidth 
                              if self:getTile(x , y) == 1 and ball.y <= Yaxis + self.brickHeight and not (ball.y < Yaxis) and (ball.x <= Xaxis + self.brickWidth and ball.x + ball.width>= Xaxis) then
                                        ball.y = Yaxis + self.brickHeight
                                        self:setTile(x ,y, 0)
                                        return true
                              end  
                    end
          end 
          return false
end
function Map:checkUpper(ball) 
          for y = 1, self.mapBirckHeight do
                    for x = 1, self.mapBirckWidth do
                              local Yaxis = (y-1) * self.brickHeight  + self.brickHeight * 2 
                              local Xaxis =  5 +  (x - 1) * self.brickWidth 
                              if self:getTile(x , y) == 1 and ball.y + ball.height >= Yaxis  and not(ball.y + ball.height  > Yaxis + self.brickHeight) and (ball.x <= Xaxis + self.brickWidth and ball.x + ball.width >= Xaxis) then
                                        ball.y = Yaxis - ball.height 
                                        self:setTile(x ,y, 0)
                                        return true
                              end  
                    end
          end 
          return false
end
function Map:checkRight(ball) 
          for y = 1, self.mapBirckHeight do
                    for x = 1, self.mapBirckWidth do
                              local Yaxis = (y-1) * self.brickHeight  + self.brickHeight * 2 
                              local Xaxis =  5 +  (x - 1) * self.brickWidth 
                              if self:getTile(x , y) == 1 and ball.x <= Xaxis + self.brickWidth  and not (ball.x < Xaxis) and (ball.y <= Yaxis + self.brickHeight and ball.y+ ball.height >= Yaxis) then
                                        ball.x = Xaxis + self.brickWidth
                                        self:setTile(x ,y, 0)
                                        return true
                              end  
                    end
          end 
          return false
end
function Map:checkLeft(ball) 
          for y = 1, self.mapBirckHeight do
                    for x = 1, self.mapBirckWidth do
                              local Yaxis = (y-1) * self.brickHeight  + self.brickHeight * 2 
                              local Xaxis =  5 +  (x - 1) * self.brickWidth 
                              if self:getTile(x , y) == 1 and ball.x + ball.width >= Xaxis and not (ball.x + ball.width > Xaxis + self.brickWidth  )  and (ball.y <= Yaxis + self.brickHeight and ball.y + ball.height >= Yaxis) then
                                        ball.x = Xaxis - ball.width
                                        self:setTile(x ,y, 0)
                                        return true
                              end  
                    end
          end 
          return false
end


function Map:render()
          for y = 1, self.mapBirckHeight do
                    for x = 1, self.mapBirckWidth do
                        local brick = self:getTile(x, y)
                        if brick == 1 then love.graphics.rectangle('line' , 5+  (x - 1) * self.brickWidth, self.mapBirckHeight * 3 + ( y - 1 ) * self.brickHeight ,self.brickWidth ,self.brickHeight  ) end
                    end
          end
end