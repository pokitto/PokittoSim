import upygame as pygame
import framebuf
import urandom as random
import spritedata
import sprite

pygame.display.init()
screen = pygame.display.set_mode() # full screen

print('display ready')

class GameObject(sprite.Sprite):
    def __init__(self, surfaces, frameOffsets):
        sprite.Sprite.__init__(self)
        self.frames = surfaces
        self.frameOffsets = frameOffsets
        self.currentFrameNum = 0;
        self.image = self.frames[self.currentFrameNum]  # current image
        self.animDur = 3;
        self.animDurCounter = self.animDur;
        self.x = 0
        self.y = 0
        self.vx = 0
        self.vy = 0

    def setvel(self, vx, vy):
        self.vx = vx
        self.vy = vy

    def update(self):

        # Advance frame if animation is set
        if self.animDur > 0:

            # if animation duration has elapsed, advance frame
            if self.animDurCounter == 0:
                self.currentFrameNum += 1
                if self.currentFrameNum >= len(self.frames):
                    self.currentFrameNum = 0

                #
                self.animDurCounter = self.animDur

                # Set current image
                self.image = self.frames[self.currentFrameNum]
                self.x += self.frameOffsets[self.currentFrameNum][0]
                self.y += self.frameOffsets[self.currentFrameNum][1]
            else:
                self.animDurCounter -= 1

        # Advance position
        self.x += self.vx
        self.y += self.vy

#
all_sprites = sprite.Group()
all_frogittos = sprite.Group()
all_cars = sprite.Group()

# Create frogitto sprites
for i in range(10):
    frogittoGob = GameObject(
        [spritedata.frogittoSurf_f1, spritedata.frogittoSurf_f2, spritedata.frogittoSurf_f3],
        [[0,-1],[0,-4],[0,-1]])

    # out of screen
    frogittoGob.x = -100
    frogittoGob.y = -100

    all_sprites.add(frogittoGob)
    all_frogittos.add(frogittoGob)

# Create blue and red car sprites
for i in range(5):
    carGob = GameObject(
        [spritedata.bluecarSurf_f1, spritedata.bluecarSurf_f2],
        [[0,0],[0,0]])

    # out of screen
    carGob.x = -100
    carGob.y = -100

    all_sprites.add(carGob)
    all_cars.add(carGob)

    carGob = GameObject(
        [spritedata.redcarSurf_f1, spritedata.redcarSurf_f2],
        [[0,0],[0,0]])

    # out of screen
    carGob.x = -100
    carGob.y = -100

    all_sprites.add(carGob)
    all_cars.add(carGob)

print('all_frogittos len=', len(all_frogittos))

vx = 0;
vy = 0;
frameNum = 0;
while True:

    #print('frameNum=',frameNum)vx

#    eventtype = pygame.event.poll(i * 10)
#    if eventtype != pygame.NOEVENT:
#        if eventtype.type() == pygame.KEYDOWN:
#            if eventtype.key() == pygame.K_RIGHT:
#                vx = 1
#            if eventtype.key() == pygame.K_LEFT:
#                vx = -1i
#            if eventtype.key() == pygame.K_UP:
#                vy = -1
#            if eventtype.key() == pygame.K_DOWN:
#                vy = 1
#        if eventtype.type() == pygame.KEYUP:
#            if eventtype.key() == pygame.K_RIGHT:
#                vx = 0
#            if eventtype.key() == pygame.K_LEFT:
#                vx = 0
#            if eventtype.key() == pygame.K_UP:
#                vy = 0
#            if eventtype.key() == pygame.K_DOWN:
#                vy = 0

#    frogittoGob.setvel(vx,vy);


    # Launch new frogitto after n frames
    if (frameNum % 20) == 0:
        # Get first free frogitto
        for s in all_frogittos:
            if s.y < -8:
                s.x = 40 + random.getrandbits(4)
                s.y = 88
                s.currentFrameNum = 0

                break

    # Launch new car after n frames
    if (frameNum % 10) == 0:
        # Get first free car
        for s in all_cars:
            if s.x < -16:
                s.x = 110
                s.y = 25 + random.getrandbits(4)
                s.setvel(-3,0)
                s.currentFrameNum = 0

                break

    all_sprites.update()
    all_sprites.draw(screen)

    pygame.display.flip()

    frameNum += 1
    if frameNum > 1000000:
        frameNum = 0;
