import Sofa
from SofaPython import Quaternion
import math
from numpy import *

class CubeController(Sofa.PythonScriptController):
    # called once graph is created, to init some stuff...
    def initGraph(self,node):
        global rootNode 
        rootNode = node.getRoot()
        self.mechanicalModel = node.getObject('DOFs')
        self.xbox = node.getObject('xboxDriver')
     
    # key and mouse events; use this to add some user interaction to your scripts 
    def onBeginAnimationStep(self,k):
        mechanicalModelPositions = self.mechanicalModel.position

        scaleValue=1
        if(self.xbox.buttonX == True) :
            scaleValue=0.99
        if(self.xbox.buttonB == True) :
            scaleValue=1.01

        for i in range(0,len(mechanicalModelPositions)) :
            for j in range(0,3) :
                mechanicalModelPositions[i][j] *= scaleValue;

        self.mechanicalModel.position = mechanicalModelPositions
        return 0 
     