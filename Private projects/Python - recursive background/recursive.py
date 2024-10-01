import pygame
import pygame_widgets
from pygame_widgets.slider import Slider
from pygame_widgets.textbox import TextBox
from pygame_widgets.toggle import Toggle

import math
import random

pygame.init()

WIDTH, HEIGHT = 1920, 1080
FRAMERATE = 60

WIN = pygame.display.set_mode((WIDTH,HEIGHT))
pygame.display.set_caption("Recursive")



BACKGROUND_COLOR = (0,0,0)
WHITE = (255,255,255)
START_R = 255
START_G = 255
START_B = 255
LINE_COLOR = (START_R,START_G,START_B)
COLOR_CHANGE_R = 0
COLOR_CHANGE_G = 0
COLOR_CHANGE_B = 0

INITIAL_LENGHT = 200
MAX_LINES = 4
REDUCING_FACTOR = 1.5
ANGLE_CHANGE_START = math.pi
ANGLE_CHANGE = math.pi/4

DRAW_MIDDLE = True
RANDOM = False

HIDE_SLIDERS = False
random.seed(1)

slider_angle = Slider(WIN, 1700, 45, 200, 20, min=2, max=32, step=0.2, initial = 4, handleColour = (180,120,255))
output_angle = TextBox(WIN, 1550, 50, 120, 20, fontSize=18, textColour = (255,255,255), colour=(0,0,0))
output_angle.setText("Angle Change")
output_angle.disable()  # Act as label instead of textbox

slider_length = Slider(WIN, 1700, 95, 200, 20, min=1.1, max=2, step=0.01, initial = 1.5, handleColour = (180,120,255))
output_length = TextBox(WIN, 1550, 100, 120, 20, fontSize=18, textColour = (255,255,255), colour=(0,0,0))
output_length.setText("Length Change")
output_length.disable()  # Act as label instead of textbox

slider_length2 = Slider(WIN, 1700, 145, 200, 20, min=100, max=600, step=1, initial = 200, handleColour = (180,120,255))
output_length2 = TextBox(WIN, 1550, 150, 120, 20, fontSize=18, textColour = (255,255,255), colour=(0,0,0))
output_length2.setText("Initial Length")
output_length2.disable()  # Act as label instead of textbox

slider_lines = Slider(WIN, 1700, 195, 200, 20, min=1, max=15, step=1, initial = 5, handleColour = (180,120,255))
output_lines = TextBox(WIN, 1550, 200, 120, 20, fontSize=18, textColour = (255,255,255), colour=(0,0,0))
output_lines.setText("Max Lines")
output_lines.disable()  # Act as label instead of textbox

toggle_3 = Toggle(WIN, 1860, 250, 40, 20, handleOnColour = (180,120,255))
output_3 = TextBox(WIN, 1760, 255, 50, 20, fontSize=18, textColour = (255,255,255), colour=(0,0,0))
output_3.setText("3 Lines")
output_3.disable()  # Act as label instead of textbox

toggle_r = Toggle(WIN, 1860, 300, 40, 20, handleOnColour = (180,120,255))
output_r = TextBox(WIN, 1760, 305, 50, 20, fontSize=18, textColour = (255,255,255), colour=(0,0,0))
output_r.setText("Random")
output_r.disable()  # Act as label instead of textbox

toggle_m = Toggle(WIN, 1860, 1040, 20, 10, handleOnColour = (180,120,255))

slider_color_ir = Slider(WIN, 1700, 350, 200, 10, min=0, max=255, step=1, initial = 255, handleColour = (180,120,255))
output_color_ir = TextBox(WIN, 1550, 355, 120, 20, fontSize=18, textColour = (255,255,255), colour=(0,0,0))
output_color_ir.setText("Initial R")
output_color_ir.disable()  # Act as label instead of textbox

slider_color_ig = Slider(WIN, 1700, 370, 200, 10, min=0, max=255, step=1, initial = 255, handleColour = (180,120,255))
output_color_ig = TextBox(WIN, 1550, 375, 120, 20, fontSize=18, textColour = (255,255,255), colour=(0,0,0))
output_color_ig.setText("Initial G")
output_color_ig.disable()  # Act as label instead of textbox

slider_color_ib = Slider(WIN, 1700, 390, 200, 10, min=0, max=255, step=1, initial = 255, handleColour = (180,120,255))
output_color_ib = TextBox(WIN, 1550, 395, 120, 20, fontSize=18, textColour = (255,255,255), colour=(0,0,0))
output_color_ib.setText("Initial B")
output_color_ib.disable()  # Act as label instead of textbox

slider_color_nr = Slider(WIN, 1700, 430, 200, 10, min=-30, max=30, step=1, initial = 0, handleColour = (180,120,255))
output_color_nr = TextBox(WIN, 1550, 435, 120, 20, fontSize=18, textColour = (255,255,255), colour=(0,0,0))
output_color_nr.setText("Change R")
output_color_nr.disable()  # Act as label instead of textbox

slider_color_nb = Slider(WIN, 1700, 450, 200, 10, min=-30, max=30, step=1, initial = 0, handleColour = (180,120,255))
output_color_nb = TextBox(WIN, 1550, 455, 120, 20, fontSize=18, textColour = (255,255,255), colour=(0,0,0))
output_color_nb.setText("Change B")
output_color_nb.disable()  # Act as label instead of textbox

slider_color_ng = Slider(WIN, 1700, 470, 200, 10, min=-30, max=30, step=1, initial = 0, handleColour = (180,120,255))
output_color_ng = TextBox(WIN, 1550, 475, 120, 20, fontSize=18, textColour = (255,255,255), colour=(0,0,0))
output_color_ng.setText("Change G")
output_color_ng.disable()  # Act as label instead of textbox


def main():
    run = True
    clock = pygame.time.Clock()
    
    go = True
    while run:
        clock.tick(FRAMERATE)
        if go:
            WIN.fill((0,0,0))
            recursive()
            pygame.display.update()
            go = False


        events = pygame.event.get()
        for event in events:
            if event.type == pygame.QUIT:
                run = False


        
        global ANGLE_CHANGE
        cur_ang = ANGLE_CHANGE
        ANGLE_CHANGE = ANGLE_CHANGE_START/slider_angle.getValue()

        global REDUCING_FACTOR
        cur_len = REDUCING_FACTOR
        REDUCING_FACTOR = slider_length.getValue()

        global INITIAL_LENGHT
        cur_len2 = INITIAL_LENGHT
        INITIAL_LENGHT = slider_length2.getValue()

        global MAX_LINES
        cur_lin = MAX_LINES
        MAX_LINES = slider_lines.getValue()

        global DRAW_MIDDLE
        cur_mid = DRAW_MIDDLE
        DRAW_MIDDLE = toggle_3.getValue()

        global RANDOM
        cur_r = RANDOM
        RANDOM = toggle_r.getValue()

        global HIDE_SLIDERS
        cur_m = HIDE_SLIDERS
        HIDE_SLIDERS = toggle_m.getValue()

        global START_R
        cur_ir = START_R
        START_R = slider_color_ir.getValue()

        global START_G
        cur_ig = START_G
        START_G = slider_color_ig.getValue()

        global START_B
        cur_ib = START_B
        START_B = slider_color_ib.getValue()

        global LINE_COLOR
        LINE_COLOR = (START_R, START_G, START_B)

        global COLOR_CHANGE_R
        cur_nr = COLOR_CHANGE_R
        COLOR_CHANGE_R = slider_color_nr.getValue()

        global COLOR_CHANGE_G
        cur_ng = COLOR_CHANGE_G
        COLOR_CHANGE_G = slider_color_ng.getValue()

        global COLOR_CHANGE_B
        cur_nb = COLOR_CHANGE_B
        COLOR_CHANGE_B = slider_color_nb.getValue()

        if cur_ang != ANGLE_CHANGE or cur_len != REDUCING_FACTOR or cur_len2 != INITIAL_LENGHT or cur_lin != MAX_LINES or cur_mid != DRAW_MIDDLE or cur_r != RANDOM or cur_m != HIDE_SLIDERS or cur_ig != START_G or cur_ir != START_R or cur_ib != START_B or cur_nr != COLOR_CHANGE_R or cur_nb != COLOR_CHANGE_B or cur_ng != COLOR_CHANGE_G:
            go = True
        
        if HIDE_SLIDERS and cur_m == False:
            slider_angle.hide()
            slider_length.hide()
            slider_length2.hide()
            slider_lines.hide()
            toggle_3.hide()
            toggle_r.hide()
            slider_color_ib.hide()
            slider_color_nb.hide()
            slider_color_ig.hide()
            slider_color_ng.hide()
            slider_color_ir.hide()
            slider_color_nr.hide()

            output_3.hide()
            output_angle.hide()
            output_length.hide()
            output_length2.hide()
            output_lines.hide()
            output_r.hide()
            output_color_ib.hide()
            output_color_nb.hide()
            output_color_ig.hide()
            output_color_ng.hide()
            output_color_ir.hide()
            output_color_nr.hide()

        if cur_m and HIDE_SLIDERS == False:
            slider_angle.show()
            slider_length.show()
            slider_length2.show()
            slider_lines.show()
            toggle_3.show()
            toggle_r.show()
            slider_color_ib.show()
            slider_color_nb.show()
            slider_color_ig.show()
            slider_color_ng.show()
            slider_color_ir.show()
            slider_color_nr.show()

            output_3.show()
            output_angle.show()
            output_length.show()
            output_length2.show()
            output_lines.show()
            output_r.show()
            output_color_ib.show()
            output_color_nb.show()
            output_color_ig.show()
            output_color_ng.show()
            output_color_ir.show()
            output_color_nr.show()

        pygame_widgets.update(events)
        pygame.display.update()


    pygame.quit()

def recursive():
    START = (WIDTH/2,HEIGHT)
    END = (WIDTH/2,HEIGHT-INITIAL_LENGHT)
    pygame.draw.line(WIN,LINE_COLOR,START,END)
    if(DRAW_MIDDLE == False):
        recursive_left(1, INITIAL_LENGHT, -math.pi/2, WIDTH/2, HEIGHT-INITIAL_LENGHT, START_R, START_G,START_B)
        recursive_right(1, INITIAL_LENGHT, -math.pi/2, WIDTH/2, HEIGHT-INITIAL_LENGHT, START_R, START_G,START_B)
    else:
        recursive_middle(1, INITIAL_LENGHT, -math.pi/2, WIDTH/2, HEIGHT-INITIAL_LENGHT, START_R, START_G,START_B)
        recursive_left(1, INITIAL_LENGHT, math.pi - ANGLE_CHANGE, WIDTH/2, HEIGHT-INITIAL_LENGHT, START_R, START_G,START_B)
        recursive_right(1, INITIAL_LENGHT, 0 + ANGLE_CHANGE, WIDTH/2, HEIGHT-INITIAL_LENGHT, START_R, START_G,START_B)
        


def recursive_left(n, len, angle, previous_x, previous_y, last_R, last_G, last_B):
    change = REDUCING_FACTOR
    if(RANDOM and n > 3):
        change = (REDUCING_FACTOR / random.random())

    angle_new = angle + ANGLE_CHANGE
    len = len / change 
    next_x = math.cos(angle_new) * len + previous_x
    next_y = math.sin(angle_new) * len + previous_y

    new_color_R = last_R-COLOR_CHANGE_R
    if new_color_R < 0:
        new_color_R = 0
    if new_color_R > 255:
        new_color_R = 255

    new_color_G = last_G-COLOR_CHANGE_G
    if new_color_G < 0:
        new_color_G = 0
    if new_color_G > 255:
        new_color_G = 255

    new_color_B = last_B-COLOR_CHANGE_B
    if new_color_B < 0:
        new_color_B = 0
    if new_color_B > 255:
        new_color_B = 255

    color = (new_color_R,new_color_G,new_color_B)

    pygame.draw.line(WIN,color,(previous_x,previous_y),(next_x,next_y))
    if n < MAX_LINES:
        recursive_left(n+1, len, angle_new, next_x, next_y, new_color_R, new_color_G, new_color_B)
        recursive_right(n+1, len, angle_new, next_x, next_y, new_color_R, new_color_G, new_color_B)
        if(DRAW_MIDDLE):
            recursive_middle(n+1, len, angle_new, next_x, next_y, new_color_R, new_color_G, new_color_B)


def recursive_right(n, len, angle, previous_x, previous_y, last_R, last_G, last_B):
    change = REDUCING_FACTOR
    if(RANDOM and n > 3):
        change = (REDUCING_FACTOR * random.random())

    angle_new = angle - ANGLE_CHANGE
    len = len / change
    next_x = math.cos(angle_new) * len + previous_x
    next_y = math.sin(angle_new) * len + previous_y

    new_color_R = last_R-COLOR_CHANGE_R
    if new_color_R < 0:
        new_color_R = 0
    if new_color_R > 255:
        new_color_R = 255

    new_color_G = last_G-COLOR_CHANGE_G
    if new_color_G < 0:
        new_color_G = 0
    if new_color_G > 255:
        new_color_G = 255

    new_color_B = last_B-COLOR_CHANGE_B
    if new_color_B < 0:
        new_color_B = 0
    if new_color_B > 255:
        new_color_B = 255

    color = (new_color_R,new_color_G,new_color_B)

    pygame.draw.line(WIN,color,(previous_x,previous_y),(next_x,next_y))
    if n < MAX_LINES:
        recursive_left(n+1, len, angle_new, next_x, next_y, new_color_R, new_color_G, new_color_B)
        recursive_right(n+1, len, angle_new, next_x, next_y, new_color_R, new_color_G, new_color_B)
        if(DRAW_MIDDLE):
            recursive_middle(n+1, len, angle_new, next_x, next_y, new_color_R, new_color_G, new_color_B)

def recursive_middle(n, len, angle, previous_x, previous_y, last_R, last_G, last_B):
    change = REDUCING_FACTOR
    if(RANDOM and n > 3):
        change = (REDUCING_FACTOR * random.random())

    len = len / change
    next_x = math.cos(angle) * len + previous_x
    next_y = math.sin(angle) * len + previous_y

    new_color_R = last_R-COLOR_CHANGE_R
    if new_color_R < 0:
        new_color_R = 0
    if new_color_R > 255:
        new_color_R = 255

    new_color_G = last_G-COLOR_CHANGE_G
    if new_color_G < 0:
        new_color_G = 0
    if new_color_G > 255:
        new_color_G = 255

    new_color_B = last_B-COLOR_CHANGE_B
    if new_color_B < 0:
        new_color_B = 0
    if new_color_B > 255:
        new_color_B = 255

    color = (new_color_R,new_color_G,new_color_B)

    pygame.draw.line(WIN,color,(previous_x,previous_y),(next_x,next_y))
    if n < MAX_LINES:
        recursive_left(n+1, len, angle, next_x, next_y, new_color_R, new_color_G, new_color_B)
        recursive_right(n+1, len, angle, next_x, next_y, new_color_R, new_color_G, new_color_B)
        if(DRAW_MIDDLE):
            recursive_middle(n+1, len, angle, next_x, next_y, new_color_R, new_color_G, new_color_B)



main()
