__declspec(naked) void LeaderboardHook_Testing()
{
	__asm {
        cmpwi r3, 0xFB //hxamapp
		bne skip_patch

        lis   r0, 0x000B
		ori   r0, r0, 0x0025 //dwMessage
		cmplw r4, r0
		bne   skip_patch

		/* create stack frame and save LR, regs */
		stwu  r1, -0xA0(r1)       
		mflr  r0
		stw   r0, 0xA4(r1)      
		bl    __savegprlr_27

		/* prepare arguments for PatchSessionViews */
		lwz  r3, 0x14(r6) // *pViews
		lwz  r4, 0x10(r6) // dwNumViews   
		li   r5, 0        // targetPropertyId = 0 (all properties)              
		lis  r6, 0x91e2   // pointer to g_newRating
		ori  r6, r6, 0x8258

        /* call PatchSessionViews(r3,r4,r5,r6) */
		bl PatchSessionViews

		/* restore registers and return function */
		bl __restgprlr_27 

		skip_patch:
		bl __return_function
	}
}
