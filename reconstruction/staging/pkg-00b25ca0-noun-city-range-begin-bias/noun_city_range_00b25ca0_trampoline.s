/* Call trampolines for the 0x00b25ca0 model test.
 *
 * These exist because the equivalent inline-asm spelling does not compile on
 * i386. The measurement block needs two "r" inputs (the call target and the
 * receiver) plus a full five-register clobber list, and GCC rejects that as
 * "impossible constraints - not enough registers" on a 6-register ABI. Two
 * workarounds were tried first and one of them is wrong in a way worth
 * recording, because it PASSED while the measurement was broken:
 *
 *   - naming only EAX and ECX as clobbered does compile, and is not a
 *     measurement. A thiscall callee may destroy EBX/ESI/EDI, so the compiler
 *     allocates a sample register to one of them, the call overwrites it, and
 *     the "ESP before/after" reading becomes a post-call register value that
 *     can happen to compare equal.
 *   - dropping the receiver input and loading ECX in a separate asm block
 *     still fails, because the five clobbers plus the target operand exhaust
 *     the allocator.
 *
 * So the two call sites are written out here, where register allocation is not
 * the compiler's problem. The discipline is the one the inline-asm version
 * intended:
 *
 *   - the receiver arrives in ECX, the thiscall receiver register;
 *   - ESP is sampled immediately BEFORE `call` and immediately AFTER the callee
 *     returns, inside this frame, with no push or pop of ours in between;
 *   - the EAX result is captured right after the return, before anything else
 *     can touch it;
 *   - the target address is loaded into EBX once and reused, so neither routine
 *     needs a scratch register it does not have.
 *
 * `call *%ebx` is a genuine indirect call, so the compiler cannot inline the
 * body under test - which is the point of the trampoline being indirect.
 *
 * The stack offsets below are not reasoned, they are MEASURED. Inside these
 * routines, after `pushl %ebx`, the frame is
 *
 *     0(%esp)  saved EBX          12(%esp)  second argument
 *     4(%esp)  return address     16(%esp)  third argument
 *     8(%esp)  first argument
 *
 * Getting this wrong is silent in the worst way: reading 8(%esp) as the call
 * target instead of the receiver loads the RECEIVER into EBX and jumps to the
 * receiver object, which segfaults inside the test fixture - a crash that reads
 * like a broken reconstruction and is not one.
 *
 * The equality of the two ESP samples is computed HERE, in assembly, and
 * returned in EAX as 1 or 0. It is deliberately not left to C++: the C++
 * version would have to read the samples back out of memory after the frame was
 * gone, which is precisely the kind of "measurement" that can be fooled.
 */

	.text

/* void pkg00b25ca0_call_entry(void* receiver, void* target, void** out_result);
 *
 * ECX on entry: receiver.  Stack, on entry: return address, receiver, target,
 * out_result.  Writes the callee's EAX return value to *out_result.
 * Preserves EBX.  Clobbers EAX only.
 */
	.globl	pkg00b25ca0_call_entry
	.type	pkg00b25ca0_call_entry, @function
pkg00b25ca0_call_entry:
	pushl	%ebx
	movl	8(%esp), %ecx		/* receiver -> ECX (thiscall) */
	movl	12(%esp), %ebx		/* target */
	call	*%ebx
	movl	16(%esp), %ebx		/* out_result */
	movl	%eax, (%ebx)
	popl	%ebx
	ret
	.size	pkg00b25ca0_call_entry, .-pkg00b25ca0_call_entry

/* int pkg00b25ca0_esp_is_balanced(void* receiver, void* target, unsigned* out_pair);
 *
 * ECX on entry: receiver.  Stack, on entry: return address, receiver, target,
 * out_pair.  Stores {ESP immediately before the call, ESP immediately after the
 * callee returned} to out_pair as two consecutive words, and returns 1 if they
 * are equal, 0 otherwise.
 *
 * Equality is the claim under test: the `call` pushes a return address and the
 * callee's return pops it, so the samples agree exactly when this body
 * contributed no stack adjustment of its own. A body that pushed a frame
 * without a matching teardown, or that popped five words on top of a callee
 * that had already popped them, shows up here as unequal - and a test that only
 * checked the returned pointer could not tell that from a correct body.
 *
 * Preserves EBX.  Clobbers EAX, ECX and the flags.
 */
	.globl	pkg00b25ca0_esp_is_balanced
	.type	pkg00b25ca0_esp_is_balanced, @function
pkg00b25ca0_esp_is_balanced:
	pushl	%ebx
	movl	8(%esp), %ecx		/* receiver -> ECX (thiscall) */
	movl	16(%esp), %ebx		/* out_pair */
	movl	12(%esp), %eax		/* target   */
	movl	%esp, (%ebx)		/* sample BEFORE the call */
	call	*%eax
	movl	%esp, 4(%ebx)		/* sample AFTER the return */
	movl	(%ebx), %eax
	cmpl	4(%ebx), %eax
	sete	%al
	movzbl	%al, %eax
	popl	%ebx
	ret
	.size	pkg00b25ca0_esp_is_balanced, .-pkg00b25ca0_esp_is_balanced
