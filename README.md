<h1>Orin Engine</h1>
<p>Java game engine made in LWJGL 3.</p>
<p>Similar to LibGDX, RayLib and MonoGame.</p>
<br>
<h3>Setup</h3>
<p>To setup, download the compiled JAR file and add them to the build path in Eclipse IDE.</p>
<p>After this, create a Main.java file and add the following example code to get you started:</p>
<br>
<code>
  public class Demonstration extends Game {
  
  	private Batch batch;
  	private Camera camera;
  
  	private Texture tex;
  
  	@Override
  	public void init() {
  		this.batch = new Batch();
  		this.camera = new Camera(Orin.graphics.getWidth(), Orin.graphics.getHeight());
  	}

    // "tick" means update but in a fancier way
  	@Override
  	public void tick(float deltaTime) {
      // Nothing to tick!
      // You could add key detection via
      // if (Orin.input.isKeyPressed(Keys.W) {
      // }
  	}

  	@Override
  	public void render() {
  		Orin.gl.clear(GL.COLOR);
  		Orin.gl.clearColor(Color.BLACK);
  		
  		this.batch.begin();
  		this.batch.setCamera(this.camera);
  		this.batch.drawTexture(this.tex, 0.0F, 0.0F, 32.0F, 32.0F);
  		this.batch.end();
  	}
  
  	@Override
  	public void exit() {
  		// No implementation since textures are disposed automatically.
  	}
  
  	public static void main(String[] args) {
  		LWJGL3 app = new LWJGL3();
  		app.setFPS(60);
  		app.create(new Demonstration());
  	}
}
</code>
