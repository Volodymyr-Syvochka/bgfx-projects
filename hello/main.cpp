#include <bgfx/bgfx.h>
#include <bgfx/bgfxplatform.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <fstream>
#include <string.h>

class Application
{
public:
	int Run( int argc, char** argv )
	{
		// Initialize the glfw
		if ( !glfwInit() )
		{
			return -1;
		}

		// Create a window
		glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );
		mWindow = glfwCreateWindow( 640, 480, "Hello World", NULL, NULL );
		if ( !mWindow )
		{
			glfwTerminate();
			return -1;
		}

		// Setup bgfx
		bgfx::PlatformData platformData;
		memset( &platformData, 0, sizeof( platformData ) );
		platformData.nwh = glfwGetWin32Window( mWindow );
		bgfx::setPlatformData( platformData );

		// Initialize the application
		Initialize( argc, argv );

		// Loop until the user closes the window
		while ( !glfwWindowShouldClose( mWindow ) )
		{
			// Poll for and process events
			glfwPollEvents();
			Update();
		}

		// Shutdown application and glfw
		int ret = Shutdown();
		glfwTerminate();
		return ret;
	}

	virtual void Initialize( int _argc, char** _argv ) = 0;
	virtual void Update() = 0;
	virtual int Shutdown() = 0;
protected:
	GLFWwindow* mWindow;
};

const bgfx::Memory* loadMem( const char* filename )
{
	std::ifstream file( filename, std::ios::binary | std::ios::ate );
	std::streamsize size = file.tellg();
	file.seekg( 0, std::ios::beg );
	const bgfx::Memory* mem = bgfx::alloc( uint32_t( size + 1 ) );
	if ( file.read( ( char* )mem->data, size ) )
	{
		mem->data[ mem->size - 1 ] = '\0';
		return mem;
	}
	return nullptr;
}

bgfx::ShaderHandle loadShader( const char* shader )
{
	return bgfx::createShader( loadMem( shader ) );
}

bgfx::ProgramHandle loadProgram( const char* vsName, const char* fsName )
{
	bgfx::ShaderHandle vs = loadShader( vsName );
	bgfx::ShaderHandle fs = loadShader( fsName );
	return createProgram( vs, fs, true );
}

class ExampleCubes : public Application
{
	void Initialize( int _argc, char** _argv )
	{
		m_width     = 640;
		m_height    = 480;
		m_reset     = BGFX_RESET_VSYNC;
		m_oldWidth  = m_width;
		m_oldHeight = m_height;

		bgfx::init( bgfx::RendererType::Direct3D11 );
		bgfx::reset( m_width, m_height, m_reset );
		bgfx::setViewClear( 0, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH, 0xff0000ff, 1.0f, 0 );

		m_program = loadProgram( "shaders/dx11/vs_hello.bin", "shaders/dx11/fs_hello.bin" );
	}

	int Shutdown()
	{
		bgfx::shutdown();
		return 0;
	}

	void Update()
	{
		int width, height;
		glfwGetWindowSize( mWindow, &width, &height );
		m_width = width;
		m_height = height;
		if ( ( m_width != m_oldWidth ) || ( m_height != m_oldHeight ) )
		{
			m_oldWidth = m_width;
			m_oldHeight = m_height;
			bgfx::reset( m_width, m_height, m_reset );
		}

		bgfx::setViewRect( 0, 0, 0, uint16_t( m_width ), uint16_t( m_height ) );
		bgfx::touch( 0 );
		bgfx::frame();
	}

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_reset;
	uint32_t m_oldWidth;
	uint32_t m_oldHeight;

	bgfx::ProgramHandle m_program;
};

int main( int argc, char** argv )
{
	ExampleCubes app;
	return app.Run( argc, argv );
}