/*
 * The MIT License (MIT)
 *
 * FXGL - JavaFX Game Library
 *
 * Copyright (c) 2015-2017 AlmasB 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.almasb.fxglgames.breakout;

import com.almasb.fxgl.annotation.SpawnSymbol;
import com.almasb.fxgl.app.FXGL;
import com.almasb.fxgl.ecs.Entity;
import com.almasb.fxgl.effect.ParticleControl;
import com.almasb.fxgl.effect.ParticleEmitter;
import com.almasb.fxgl.effect.ParticleEmitters;
import com.almasb.fxgl.entity.Entities;
import com.almasb.fxgl.entity.SpawnData;
import com.almasb.fxgl.entity.TextEntityFactory;
import com.almasb.fxgl.entity.component.CollidableComponent;
import com.almasb.fxgl.physics.BoundingShape;
import com.almasb.fxgl.physics.HitBox;
import com.almasb.fxgl.physics.PhysicsComponent;
import com.almasb.fxgl.physics.box2d.dynamics.BodyType;
import com.almasb.fxgl.physics.box2d.dynamics.FixtureDef;
import com.almasb.fxglgames.breakout.control.BallControl;
import com.almasb.fxglgames.breakout.control.BatControl;
import com.almasb.fxglgames.breakout.control.BrickControl;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

/**
 * @author Almas Baimagambetov 
 */
public class BreakoutFactory implements TextEntityFactory {

    @SpawnSymbol('1')
    public Entity newBrick(SpawnData data) {
        return Entities.builder()
                .from(data)
                .type(BreakoutType.BRICK)
                .viewFromNodeWithBBox(FXGL.getAssetLoader().loadTexture("brick_blue.png", 232 / 3, 104 / 3))
                .with(new PhysicsComponent(), new CollidableComponent(true))
                .with(new BrickControl())
                .build();
    }

    @SpawnSymbol('9')
    public Entity newBat(SpawnData data) {
        PhysicsComponent physics = new PhysicsComponent();
        physics.setBodyType(BodyType.KINEMATIC);

        return Entities.builder()
                .from(data)
                .type(BreakoutType.BAT)
                .at(FXGL.getSettings().getWidth() / 2 - 50, 30)
                .viewFromNodeWithBBox(FXGL.getAssetLoader().loadTexture("bat.png", 464 / 3, 102 / 3))
                .with(physics, new CollidableComponent(true))
                .with(new BatControl())
                .build();
    }

    @SpawnSymbol('2')
    public Entity newBall(SpawnData data) {
        PhysicsComponent physics = new PhysicsComponent();
          physics.setBodyType(BodyType.DYNAMIC);
            physics.setFixtureDef(new FixtureDef().restitution(1f).density(0.03f));

               ParticleEmitter emitter = ParticleEmitters.newFireEmitter();
			   
			   
			   emitter.numParticles = 5;
               emitter.setEmissionRate = 0.5 ;

        return Entities.builder()
                .from(data)
                .type(BreakoutType.BALL)
                .bbox(new HitBox("Main", BoundingShape.circle(10)))
                .viewFromNode(new Circle(10, Color.LIGHTCORAL))
                .with(physics, new CollidableComponent(true))
                .with(new BallControl(), new ParticleControl(emitter))
                .build();
    }

    @Override
    public char emptyChar() {
        return '0';
    }

    @Override
    public int blockWidth() {
        return 40;
    }

    @Override
    public int blockHeight() {
        return 40;
    }
}
